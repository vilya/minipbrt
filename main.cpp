// Copyright 2019 Vilya Harvey
#include "minipbrt.h"

#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

namespace minipbrt {

  //
  // Forward declarations
  //

  static void print_error(const Error* err);
  static void print_scene_info(const Scene* scene);

  static void print_accelerator(const Accelerator* accel);
  static void print_camera(const Camera* camera);
  static void print_film(const Film* film);
  static void print_filter(const Filter* filter);
  static void print_integrator(const Integrator* integrator);
  static void print_sampler(const Sampler* sampler);

  static void print_shapes_summary(const Scene* scene);


  //
  // Helper functions
  //

  template <class T>
  const char* lookup(const char* values[], T enumVal)
  {
    return values[static_cast<uint32_t>(enumVal)];
  }


  //
  // Functions
  //

  static void print_error(const Error* err)
  {
    if (err == nullptr) {
      fprintf(stderr, "Parsing failed but the Error object was null.\n");
      return;
    }

    fprintf(stderr, "[%s, line %lld, column %lld] %s\n",
            err->filename(),
            err->line(),
            err->column(),
            err->message());
  }


  static void print_scene_info(const Scene* scene)
  {
    if (scene->accelerator) {
      print_accelerator(scene->accelerator);
    }
    if (scene->camera) {
      print_camera(scene->camera);
    }
    if (scene->film) {
      print_film(scene->film);
    }
    if (scene->filter) {
      print_filter(scene->filter);
    }
    if (scene->integrator) {
      print_integrator(scene->integrator);
    }
    if (scene->sampler) {
      print_sampler(scene->sampler);
    }
    if (scene->outsideMedium) {
      printf("Outside medium is \"%s\"\n", scene->outsideMedium->mediumName);
    }

    printf("==== World Summary ====\n");
    printf("%10u shapes\n",       uint32_t(scene->shapes.size()));
    printf("%10u objects\n",      uint32_t(scene->objects.size()));
    printf("%10u instances\n",    uint32_t(scene->instances.size()));
    printf("%10u lights\n",       uint32_t(scene->lights.size()));
    printf("%10u area lights\n",  uint32_t(scene->areaLights.size()));
    printf("%10u materials\n",    uint32_t(scene->materials.size()));
    printf("%10u textures\n",     uint32_t(scene->textures.size()));
    printf("%10u mediums\n",      uint32_t(scene->mediums.size()));

    print_shapes_summary(scene);
  }


  static void print_accelerator(const Accelerator* accel)
  {
    const char* accelTypes[] = { "bvh", "kdtree" };
    printf("==== Accelerator ====\n");
    printf("Type: %s\n", lookup(accelTypes, accel->type()));
    switch (accel->type()) {
    case AcceleratorType::BVH:
      {
        const char* splitMethods[] = { "sah", "middle", "equal", "hlbvh" };
        const BVHAccelerator* bvh = dynamic_cast<const BVHAccelerator*>(accel);
        printf("maxnodeprims = %d\n", bvh->maxnodeprims);
        printf("splitmethod  = \"%s\"\n", lookup(splitMethods, bvh->splitmethod));
      }
      break;
    case AcceleratorType::KdTree:
      {
        const KdTreeAccelerator* kdtree = dynamic_cast<const KdTreeAccelerator*>(accel);
        printf("intersectcost = %d\n", kdtree->intersectcost);
        printf("traversalcost = %d\n", kdtree->traversalcost);
        printf("emptybonus = %f\n", kdtree->emptybonus);
        printf("maxprims = %d\n", kdtree->maxprims);
        printf("maxdepth = %d\n", kdtree->maxdepth);
      }
      break;
    }
    printf("\n");
  }


  static void print_camera(const Camera* camera)
  {
    const char* cameraTypes[] = { "perspective", "orthographic", "environment", "realistic" };
    printf("==== Camera ====\n");
    printf("Type: %s\n", lookup(cameraTypes, camera->type()));
    printf("shutteropen      = %f\n", camera->shutteropen);
    printf("shutterclose     = %f\n", camera->shutterclose);
    switch (camera->type()) {
    case CameraType::Perspective:
      {
        const PerspectiveCamera* typedCam = dynamic_cast<const PerspectiveCamera*>(camera);
        printf("frameaspectratio = %f\n", typedCam->frameaspectratio);
        printf("screenwindow     = [ %f, %f, %f, %f ]\n", typedCam->screenwindow[0], typedCam->screenwindow[1], typedCam->screenwindow[2], typedCam->screenwindow[3]);
        printf("lensradius       = %f\n", typedCam->lensradius);
        printf("focaldistance    = %f\n", typedCam->focaldistance);
        printf("fov              = %f\n", typedCam->fov);
        printf("halffov          = %f\n", typedCam->halffov);
      }
      break;
    case CameraType::Orthographic:
      {
        const OrthographicCamera* typedCam = dynamic_cast<const OrthographicCamera*>(camera);
        printf("frameaspectratio = %f\n", typedCam->frameaspectratio);
        printf("screenwindow     = [ %f, %f, %f, %f ]\n", typedCam->screenwindow[0], typedCam->screenwindow[1], typedCam->screenwindow[2], typedCam->screenwindow[3]);
        printf("lensradius       = %f\n", typedCam->lensradius);
        printf("focaldistance    = %f\n", typedCam->focaldistance);
      }
      break;
    case CameraType::Environment:
      {
        const EnvironmentCamera* typedCam = dynamic_cast<const EnvironmentCamera*>(camera);
        printf("frameaspectratio = %f\n", typedCam->frameaspectratio);
        printf("screenwindow     = [ %f, %f, %f, %f ]\n", typedCam->screenwindow[0], typedCam->screenwindow[1], typedCam->screenwindow[2], typedCam->screenwindow[3]);
      }
      break;
    case CameraType::Realistic:
      {
        const RealisticCamera* typedCam = dynamic_cast<const RealisticCamera*>(camera);
        printf("lensfile         = \"%s\"\n", typedCam->lensfile);
        printf("aperturediameter = %f\n", typedCam->aperturediameter);
        printf("focusdistance    = %f\n", typedCam->focusdistance);
        printf("simpleweighting  = %s\n", typedCam->simpleweighting ? "true" : "false");
      }
      break;
    }
    printf("\n");
  }


  static void print_film(const Film* film)
  {
    const char* filmTypes[] = { "image" };
    printf("==== Film ====\n");
    printf("Type: %s\n", lookup(filmTypes, film->type()));
    switch(film->type()) {
    case FilmType::Image:
      {
        const ImageFilm* imagefilm = dynamic_cast<const ImageFilm*>(film);
        printf("xresolution        = %d\n", imagefilm->xresolution);
        printf("yresolution        = %d\n", imagefilm->yresolution);
        printf("cropwindow         = [ %f, %f, %f, %f ]\n", imagefilm->cropwwindow[0], imagefilm->cropwwindow[1], imagefilm->cropwwindow[2], imagefilm->cropwwindow[3]);
        printf("scale              = %f\n", imagefilm->scale);
        printf("maxsampleluminance = %f\n", imagefilm->maxsampleluminance);
        printf("diagonal           = %f mm\n", imagefilm->diagonal);
        printf("filename           = %s\n", imagefilm->filename);
      }
      break;
    }

    printf("\n");
  }


  static void print_filter(const Filter* filter)
  {
    const char* filterTypes[] = { "box", "gaussian", "mitchell", "sinc", "triangle" };
    printf("==== Filter ====\n");
    printf("Type: %s\n", lookup(filterTypes, filter->type()));
    printf("xwidth = %f\n", filter->xwidth);
    printf("ywidth = %f\n", filter->ywidth);
    switch (filter->type()) {
    case FilterType::Box:
      break;
    case FilterType::Gaussian:
      {
        const GaussianFilter* gaussian = dynamic_cast<const GaussianFilter*>(filter);
        printf("alpha  = %f\n", gaussian->alpha);
      }
      break;
    case FilterType::Mitchell:
      {
        const MitchellFilter* mitchell = dynamic_cast<const MitchellFilter*>(filter);
        printf("B      = %f\n", mitchell->B);
        printf("C      = %f\n", mitchell->C);
      }
      break;
    case FilterType::Sinc:
      {
        const SincFilter* sinc = dynamic_cast<const SincFilter*>(filter);
        printf("tau    = %f\n", sinc->tau);
      }
      break;
    case FilterType::Triangle:
      break;
    }
    printf("\n");
  }


  static void print_integrator(const Integrator* integrator)
  {
    printf("==== Integrator ====\n");
    // TODO
    printf("\n");
  }


  static void print_sampler(const Sampler* sampler)
  {
    printf("==== Sampler ====\n");
    // TODO
    printf("\n");
  }


  static void print_shapes_summary(const Scene* scene)
  {
    constexpr uint32_t kNumShapeTypes = static_cast<uint32_t>(ShapeType::PLYMesh) + 1;

    uint32_t numShapesByType[kNumShapeTypes];
    for (uint32_t i = 0; i < kNumShapeTypes; i++) {
      numShapesByType[i] = 0;
    }
    for (const Shape* shape : scene->shapes) {
      numShapesByType[static_cast<uint32_t>(shape->type())]++;
    }

    const char* shapeTypes[] = { "cones", "curves", "cylinders", "disks", "hyperboloids", "paraboloids", "spheres", "trianglemeshes", "heightfields", "loopsubdivs", "nurbses", "plymeshes", nullptr };

    printf("==== Shapes ====\n");
    for (uint32_t i = 0; i < kNumShapeTypes; i++) {
      printf("%7u %s\n", numShapesByType[i], shapeTypes[i]);
    }
  }

} // namespace minipbrt


int main(int argc, char** argv)
{
  if (argc <= 1) {
    fprintf(stderr, "No input file provided.\n");
    return EXIT_SUCCESS;
  }

  minipbrt::Parser parser;
  bool ok = parser.parse(argv[1]);
  if (!ok) {
    minipbrt::print_error(parser.get_error());
    return EXIT_FAILURE;
  }
  else {
    minipbrt::Scene* scene = parser.take_scene();
    minipbrt::print_scene_info(scene);
    delete scene;
    return EXIT_SUCCESS;
  }
}
