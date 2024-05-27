
/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "Raytracer.hpp"

using namespace Raytracer;
using namespace Math;

__attribute__((constructor))
void init() {
    srand(time(NULL));
}

void bouncing_spheres()
{
    std::clog << "Building scene: bouncing spheres" << std::endl;
    HittableList world;

    auto checker = make_shared<ChessBoard>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));
    world.add(make_shared<Sphere>(Point3D(0,-1000,0), 1000, make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3D center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Point3D(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Color::random() * Color::random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    auto center2 = center + Vector3D(0, random_double(0, 0.5), 0);
                    world.add(make_shared<Sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // Metal
                    auto albedo = Color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Point3D(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Point3D(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Point3D(4, 1, 0), 1.0, material3));

    world = HittableList(make_shared<BVHNode>(world));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1200;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.origin = Point3D(13,2,3);
    cam.direction   = Vector3D(0,0,0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0.6;
    cam.focus_distance    = 10.0;

    cam.render(world);
}

void checkered_spheres() {
    std::clog << "Building scene: checkered_spheres" << std::endl;
    HittableList world;

    auto checker = make_shared<ChessBoard>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));

    world.add(make_shared<Sphere>(Point3D(0,-10, 0), 10, make_shared<Lambertian>(checker)));
    world.add(make_shared<Sphere>(Point3D(0, 10, 0), 10, make_shared<Lambertian>(checker)));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.origin = Point3D(13,2,3);
    cam.direction   = Point3D(0,0,0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void earth() {
    auto earth_texture = make_shared<Image>(TEXTURES_PATH "earthmap.png");
    auto earth_surface = make_shared<Lambertian>(earth_texture);
    auto globe = make_shared<Sphere>(Point3D(0,0,0), 2, earth_surface);

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.origin = Point3D(0,0,12);
    cam.direction   = Point3D(0,0,0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(HittableList(globe));
}

void perlin_spheres()
{
    HittableList world;

    auto pertext = make_shared<Noise>(4);
    world.add(make_shared<Sphere>(Point3D(0,-1000,0), 1000, make_shared<Lambertian>(pertext)));
    world.add(make_shared<Sphere>(Point3D(0,2,0), 2, make_shared<Lambertian>(pertext)));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0.70, 0.80, 1.00);

    cam.vfov     = 20;
    cam.origin = Point3D(13,2,3);
    cam.direction   = Point3D(0,0,0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void plane()
{
    HittableList world;

    auto left_red = make_shared<Lambertian>(Color(1.0, 0.2, 0.2));
    auto right_blue = make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    auto back_green = make_shared<Lambertian>(Color(0.2, 1.0, 0.2));
    auto upper_orange = make_shared<Lambertian>(Color(1.0, 0.5, 0.0));
    auto lower_teal = make_shared<Lambertian>(Color(0.2, 0.8, 0.8));

    world.add(make_shared<Plane>(Point3D(-3, -2, 5), Vector3D(0, 0, -4), Vector3D(0, 4, 0), left_red));
    world.add(make_shared<Plane>(Point3D(3, -2, 1), Vector3D(0, 0, 4), Vector3D(0, 4, 0), right_blue));
    world.add(make_shared<Plane>(Point3D(-2, -2, 0), Vector3D(4, 0, 0), Vector3D(0, 4, 0), back_green));
    world.add(make_shared<Plane>(Point3D(-2, 3, 1), Vector3D(4, 0, 0), Vector3D(0, 0, 4), upper_orange));
    world.add(make_shared<Plane>(Point3D(-2, -3, 5), Vector3D(4, 0, 0), Vector3D(0, 0, -4), lower_teal));

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0.70, 0.80, 1.00);

    cam.vfov     = 80;
    cam.origin = Point3D(0,0,9);
    cam.direction   = Point3D(0,0,0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

// Just a blue cylinder in 3D
void simple_cylinder()
{
    HittableList world;

    auto blue = make_shared<Lambertian>(Color(0.2, 0.2, 1.0));
    world.add(make_shared<Cylinder>(Point3D(0, 0, 0), 1, 2, blue));

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0.70, 0.80, 1.00);

    cam.vfov     = 90; // Increase the field of view to 90 degrees
    cam.origin = Point3D(4,4,4); // Move the camera further away to the point (4,4,4)
    cam.direction = Point3D(0,0,0); // Point the camera towards the origin (0,0,0)
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void simple_light()
{
    HittableList world;

    auto pertext = make_shared<Noise>(4);
    world.add(make_shared<Sphere>(Point3D(0,-1000,0), 1000, make_shared<Lambertian>(pertext)));
    world.add(make_shared<Sphere>(Point3D(0,2,0), 2, make_shared<Lambertian>(pertext)));

    auto difflight = make_shared<Diffuse>(Color(4, 4, 4));
    // world.add(make_shared<Sphere>(Point3D(0, 7, 0), 2, difflight));
    world.add(make_shared<Plane>(Point3D(3, 1, -2), Vector3D(2, 0, 0), Vector3D(0, 2, 0), difflight));

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1920;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0, 0, 0);

    cam.vfov     = 20;
    cam.origin = Point3D(26,3,6);
    cam.direction   = Point3D(0,2,0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void simple_light_cylinder()
{
    HittableList world;

    auto pertext = make_shared<Noise>(4);
    world.add(make_shared<Sphere>(Point3D(0,-1000,0), 1000, make_shared<Lambertian>(pertext)));
    world.add(make_shared<Cylinder>(Point3D(0,1,0), 1.3, 2, make_shared<Lambertian>(pertext)));

    auto difflight = make_shared<Diffuse>(Color(4, 4, 4));
    // world.add(make_shared<Sphere>(Point3D(0, 7, 0), 2, difflight));
    world.add(make_shared<Plane>(Point3D(3, 1, -2), Vector3D(2, 0, 0), Vector3D(0, 4, 0), difflight)); // Increase the y-coordinate of the light source

    Camera cam;

    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 1920;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0, 0, 0);

    cam.vfov     = 20;
    cam.origin = Point3D(26,5,6); // Move the camera higher
    cam.direction   = Point3D(0,-1,0); // Point the camera downwards
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void cornell_box()
{
    HittableList world;

    auto red = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<Diffuse>(Color(15, 15, 15));

    world.add(make_shared<Plane>(Point3D(555, 0, 0), Vector3D(0, 555, 0), Vector3D(0, 0, 555), green));
    world.add(make_shared<Plane>(Point3D(0, 0, 0), Vector3D(0, 555, 0), Vector3D(0, 0, 555), red));
    world.add(make_shared<Plane>(Point3D(343, 554, 332), Vector3D(-130, 0, 0), Vector3D(0, 0, -105), light));

    world.add(make_shared<Plane>(Point3D(0, 0, 0), Vector3D(555, 0, 0), Vector3D(0, 0, 555), white));
    world.add(make_shared<Plane>(Point3D(555, 555, 555), Vector3D(-555, 0, 0), Vector3D(0, 0, -555), white));
    world.add(make_shared<Plane>(Point3D(0, 0, 555), Vector3D(555, 0, 0), Vector3D(0, 555, 0), white));

    // world.add(Box(Point3D(130, 0, 65), Point3D(295, 165, 230), white));
    // world.add(Box(Point3D(265, 0, 295), Point3D(430, 330, 460), white));

    shared_ptr<Hittable> box1 = make_shared<Rotation>(Box(Point3D(0, 0, 0), Point3D(165, 330, 165), white), 15);
    box1 = make_shared<Translation>(box1, Vector3D(265, 0, 295));
    world.add(box1);

    shared_ptr<Hittable> box2 = make_shared<Rotation>(Box(Point3D(0, 0, 0), Point3D(165, 165, 165), white), -18);
    box2 = make_shared<Translation>(box2, Vector3D(130, 0, 65));
    world.add(box2);

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0, 0, 0);

    cam.vfov     = 40;
    cam.origin = Point3D(278, 278, -800);
    cam.direction   = Point3D(278, 278, 0);
    cam.vup      = Vector3D(0, 1, 0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void cornell_smoke()
{
    HittableList world;

    auto red   = make_shared<Lambertian>(Color(.65, .05, .05));
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    auto green = make_shared<Lambertian>(Color(.12, .45, .15));
    auto light = make_shared<Diffuse>(Color(7, 7, 7));

    world.add(make_shared<Plane>(Point3D(555,0,0), Vector3D(0,555,0), Vector3D(0,0,555), green));
    world.add(make_shared<Plane>(Point3D(0,0,0), Vector3D(0,555,0), Vector3D(0,0,555), red));
    world.add(make_shared<Plane>(Point3D(113,554,127), Vector3D(330,0,0), Vector3D(0,0,305), light));
    world.add(make_shared<Plane>(Point3D(0,555,0), Vector3D(555,0,0), Vector3D(0,0,555), white));
    world.add(make_shared<Plane>(Point3D(0,0,0), Vector3D(555,0,0), Vector3D(0,0,555), white));
    world.add(make_shared<Plane>(Point3D(0,0,555), Vector3D(555,0,0), Vector3D(0,555,0), white));

    shared_ptr<Hittable> box1 = Box(Point3D(0,0,0), Point3D(165,330,165), white);
    box1 = make_shared<Rotation>(box1, 15);
    box1 = make_shared<Translation>(box1, Vector3D(265,0,295));

    shared_ptr<Hittable> box2 = Box(Point3D(0,0,0), Point3D(165,165,165), white);
    box2 = make_shared<Rotation>(box2, -18);
    box2 = make_shared<Translation>(box2, Vector3D(130,0,65));

    world.add(make_shared<Density>(box1, 0.01, Color(0,0,0)));
    world.add(make_shared<Density>(box2, 0.01, Color(1,1,1)));

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.background        = Color(0,0,0);

    cam.vfov     = 40;
    cam.origin = Point3D(278, 278, -800);
    cam.direction   = Point3D(278, 278, 0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

void final_scene(int image_width, int samples_per_pixel, int max_depth) {
    HittableList boxes1;
    auto ground = make_shared<Lambertian>(Color(0.48, 0.83, 0.53));

    int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_double(1,101);
            auto z1 = z0 + w;

            boxes1.add(Box(Point3D(x0,y0,z0), Point3D(x1,y1,z1), ground));
        }
    }

    HittableList world;

    world.add(make_shared<BVHNode>(boxes1));

    auto light = make_shared<Diffuse>(Color(7, 7, 7));
    world.add(make_shared<Plane>(Point3D(123,554,147), Vector3D(300,0,0), Vector3D(0,0,265), light));

    auto center1 = Point3D(400, 400, 200);
    auto center2 = center1 + Vector3D(30,0,0);
    auto sphere_material = make_shared<Lambertian>(Color(0.7, 0.3, 0.1));
    world.add(make_shared<Sphere>(center1, center2, 50, sphere_material));

    world.add(make_shared<Sphere>(Point3D(260, 150, 45), 50, make_shared<Dielectric>(1.5)));
    world.add(make_shared<Sphere>(
        Point3D(0, 150, 145), 50, make_shared<Metal>(Color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<Sphere>(Point3D(360,150,145), 70, make_shared<Dielectric>(1.5));
    world.add(boundary);
    world.add(make_shared<Density>(boundary, 0.2, Color(0.2, 0.4, 0.9)));
    boundary = make_shared<Sphere>(Point3D(0,0,0), 5000, make_shared<Dielectric>(1.5));
    world.add(make_shared<Density>(boundary, .0001, Color(1,1,1)));

    auto emat = make_shared<Lambertian>(make_shared<Image>("earthmap.png"));
    world.add(make_shared<Sphere>(Point3D(400,200,400), 100, emat));
    auto pertext = make_shared<Noise>(0.2);
    world.add(make_shared<Sphere>(Point3D(220,280,300), 80, make_shared<Lambertian>(pertext)));

    HittableList boxes2;
    auto white = make_shared<Lambertian>(Color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<Sphere>(Point3D::random(0,165), 10, white));
    } // 165 = cube size, 10 = sphere size

    world.add(make_shared<Translation>(
        make_shared<BVHNode>(boxes2),
        Vector3D(100,270,395) // Position of the cube
    ));

    Camera cam;

    cam.aspect_ratio      = 1.0;
    cam.image_width       = image_width;
    cam.samples_per_pixel = samples_per_pixel;
    cam.max_depth         = max_depth;
    cam.background        = Color(0,0,0);

    cam.vfov     = 40;
    cam.origin = Point3D(478, 278, -600);
    cam.direction   = Point3D(278, 278, 0);
    cam.vup      = Vector3D(0,1,0);

    cam.defocus_angle = 0;

    cam.render(world);
}

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <scene_file>" << std::endl;
        return 84;
    }

    Parser parser(av[1]);
    parser.getScene().render();

    // checkered_spheres();
    // bouncing_spheres();
    // earth();
    // perlin_spheres();
    // plane();
    // simple_light();
    // cornell_box();
    // cornell_smoke();
    // simple_cylinder();;
    // final_scene(400, 50, 50);
}
