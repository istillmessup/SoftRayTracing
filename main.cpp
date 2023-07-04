#include "common.h"
#include "camera.h"

#include "hittable/sphere.h"
#include "hittable/bvh_node.h"
#include "hittable/box.h"
#include "hittable/translate.h"
#include "hittable/rotate_y.h"

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"
#include "materials/diffuse_light.h"

#include "pdf/hittable_pdf.h"
#include "pdf/cosine_pdf.h"
#include "pdf/mixture_pdf.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <fstream>

vec3 ray_color(const ray& r, const vec3& background, const hittable& world, const shared_ptr<hittable>& light, int depth) {
    hit_record rec;

    if (depth <= 0) return {0, 0, 0};
    // t_min = 0.001为了防止当t很小时反射光线再次与自己相交
    if (!world.hit(r, 0.001, DOUBLE_INFINITY, rec)) {
        return background;
    }
    scatter_record srec;
    // 命中非光源返回0，命中光源返回光照颜色
    color emitted = rec.material_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
    // scatter() 命中光源返回false，命中物体返回true
    if (!rec.material_ptr->scatter(r, rec, srec)) {
        return emitted;
    }
    // 镜面反射不需要采样
    if (srec.is_specular) {
        return srec.albedo * ray_color(srec.specular_ray, background, world, light, depth - 1);
    }
    // 在光源方向上采样
    auto light_ptr = make_shared<hittable_pdf>(light, rec.p);
    // 混合光源采样和半球随机采样
    mixture_pdf mixed_pdf(light_ptr, srec.pdf_ptr);
    ray scattered = ray(rec.p, mixed_pdf.generate());
    double pdf_val = mixed_pdf.value(scattered.direction());

    // 递归光照方向：交点法线方向上的相切单位球内
    return emitted + srec.albedo * rec.material_ptr->scattering_pdf(r, rec, scattered)
                            * ray_color(scattered, background, world, light, depth - 1)
                            / pdf_val;
}

hittable_list random_scene() {
    hittable_list world;

    // 地面，用一个很大的球表示
    auto checker = make_shared<checker_texture>(
            make_shared<constant_texture>(vec3(0.2, 0.3, 0.1)),
            make_shared<constant_texture>(vec3(0.9, 0.9, 0.9))
            );
    world.add(make_shared<sphere>(
            vec3(0, -1000, 0), 1000, make_shared<lambertian>(checker)
            ));

    for (int j = -11; j < 11; ++j) {
        for (int k = -11; k < 11; ++k) {
            auto choose_mat = random_double();
            vec3 center(j + 0.9 * random_double(), 0.2, k + 0.9 * random_double());
            if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // 漫反射
                    auto albedo = vec3::random() * vec3::random();
                    world.add(
                            make_shared<sphere>(center, 0.2, make_shared<lambertian>(make_shared<constant_texture>(albedo))
                            ));
                }
                else if (choose_mat < 0.95) {
                    // 金属
                    auto albedo = vec3::random(.5, 1);
                    auto fuzz = random_double(0, .5);
                    world.add(
                            make_shared<sphere>(center, 0.2, make_shared<metal>(albedo, fuzz)
                            ));
                }
                else {
                    // 镜面
                    world.add(make_shared<sphere>(center, 0.2, make_shared<dielectric>(1.5)));
                }
            }
        }
    }
    world.add(
            make_shared<sphere>(vec3(0, 1, 0), 1.0, make_shared<dielectric>(1.5)
            ));
    world.add(
            make_shared<sphere>(vec3(-4, 1, 0), 1.0, make_shared<lambertian>(make_shared<constant_texture>(vec3(0.4, 0.2, 0.1)))
            ));
    world.add(
            make_shared<sphere>(vec3(4, 1, 0), 1.0, make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)
            ));
    return static_cast<hittable_list>(make_shared<bvh_node>(world));
}

hittable_list two_perlin_spheres() {
    hittable_list objects;

    auto perlin_texture = make_shared<noise_texture>(4.0);
    objects.add(make_shared<sphere>(vec3(0,-1000, 0), 1000, make_shared<lambertian>(perlin_texture)));
    objects.add(make_shared<sphere>(vec3(0, 2, 0), 2, make_shared<lambertian>(perlin_texture)));

    // 光源
    auto difflight = make_shared<diffuse_light>(make_shared<constant_texture>(vec3(4, 4, 4)));
    objects.add(make_shared<rectangle>(Z, 3, 5, 1, 3, -2, difflight));
    return objects;
}

hittable_list earth() {
    int nx, ny, nn;
    unsigned char* texture_data = stbi_load("../earth.jpg", &nx, &ny, &nn, 0);

    auto earth_surface = make_shared<lambertian>(make_shared<image_texture>(texture_data, nx, ny));
    auto globe = make_shared<sphere>(vec3(0, 0, 0), 2, earth_surface);

    return hittable_list(globe);
}

hittable_list cornell_box() {
    hittable_list objects;

    auto red = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.65, 0.05, 0.05)));
    auto white = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
    auto green = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.12, 0.45, 0.15)));
    auto light = make_shared<diffuse_light>(make_shared<constant_texture>(color(15, 15, 15)));

    objects.add(make_shared<rectangle>(X, 0, 555, 0, 555, 555, green));
    objects.add(make_shared<rectangle>(X, 0, 555, 0, 555, 0, red));
    objects.add(make_shared<rectangle>(Y, 0, 555, 0, 555, 0, white));
    objects.add(make_shared<rectangle>(Z, 0, 555, 0, 555, 555, white));
    objects.add(make_shared<rectangle>(Y, 0, 555, 0, 555, 555, white));
    objects.add(make_shared<rectangle>(Y, 213, 343, 227, 332, 554, light));

    shared_ptr<hittable> box1 = make_shared<box>(vec3(0, 0, 0), vec3(165, 330, 165), white);
    box1 = make_shared<rotate_y>(box1, 15);
    box1 = make_shared<translate>(box1, vec3(265, 0, 295));
    objects.add(box1);

    /*shared_ptr<hittable> box2 = make_shared<box>(vec3(0, 0, 0), vec3(165, 165, 165), white);
    box2 = make_shared<rotate_y>(box2,-18);
    box2 = make_shared<translate>(box2, vec3(130, 0, 65));
    objects.add(box2);*/

    objects.add(make_shared<sphere>(point3(190, 90, 190), 90 , white));

    return objects;
}

int main() {
    std::ofstream out("../img.ppm");

    const int image_width = 200;
    const int image_height = 200;
    const auto aspect_ratio = double(image_width) / image_height;
    const int samples_per_pixel = 1000;
    const int max_depth = 50;
    const vec3 background(0, 0, 0);

    // 相机
    vec3 lookfrom(278, 278, -800);
    vec3 lookat(278, 278, 0);
    vec3 vup(0, 1, 0);
    auto dist_to_focus = 10;
    auto aperture = 0.0; // 光圈直径

    camera my_camera(lookfrom, lookat, vup, 40, aspect_ratio, aperture, dist_to_focus);

    auto world = cornell_box();
    auto light = make_shared<hittable_list>();
    light->add(make_shared<rectangle>(Y, 213, 343, 227, 332, 554, shared_ptr<material>()));
    // light->add(make_shared<sphere>(point3(190, 90, 190), 90, shared_ptr<material>()));

    if (out.is_open())
    {
        out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = image_height-1; j >= 0; --j) {
            std::cerr << "\rScan lines remaining: " << j + 1 << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                vec3 color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (double(i) + random_double()) / image_width;
                    auto v = (double(j) + random_double()) / image_height;
                    ray r = my_camera.get_ray(u, v);
                    color += ray_color(r, background, world, light, max_depth);
                }
                color.write_color(out, samples_per_pixel);
            }
        }
        out.close();
    }
}
