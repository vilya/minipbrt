// Copyright 2019 Vilya Harvey
#include "minipbrt.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <string>

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

  static void print_world_summary(const Scene* scene);
  static void print_shapes_summary(const Scene* scene);
  static void print_lights_summary(const Scene* scene);
  static void print_area_lights_summary(const Scene* scene);
  static void print_materials_summary(const Scene* scene);
  static void print_textures_summary(const Scene* scene);
  static void print_mediums_summary(const Scene* scene);

  static void print_triangle_mesh_summary(const Scene* scene);

  static uint64_t triangle_mesh_bytes(const TriangleMesh* trimesh);


  //
  // Helper functions
  //

  template <class T>
  const char* lookup(const char* values[], T enumVal)
  {
    return values[static_cast<uint32_t>(enumVal)];
  }


  static uint32_t num_digits(uint32_t n)
  {
    uint32_t numDigits = 0;
    do {
      n /= 10;
      ++numDigits;
    } while (n > 0);
    return numDigits;
  }


  template <class T>
  static void histogram_by_type(const std::vector<T*>& values, uint32_t n, uint32_t histogram[])
  {
    for (uint32_t i = 0; i < n; i++) {
      histogram[i] = 0;
    }
    for (const T* value : values) {
      histogram[static_cast<uint32_t>(value->type())]++;
    }
  }


  static void print_histogram(uint32_t n, const uint32_t histogram[], const char* names[])
  {
    uint32_t maxDigits = 1;
    for (uint32_t i = 0; i < n; i++) {
      uint32_t numDigits = num_digits(histogram[i]);
      if (numDigits > maxDigits) {
        maxDigits = numDigits;
      }
    }

    for (uint32_t i = 0; i < n; i++) {
      if (histogram[i] > 0) {
        printf("%*u %s\n", maxDigits, histogram[i], names[i]);
      }
    }

    printf("\n");
  }


  template <class T, uint32_t N>
  static void print_histogram_by_type(const std::vector<T*>& values, const char* names[])
  {
    uint32_t histogram[N];
    histogram_by_type(values, N, histogram);
    print_histogram(N, histogram, names);
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

    print_world_summary(scene);

    print_shapes_summary(scene);
    print_lights_summary(scene);
    print_area_lights_summary(scene);
    print_materials_summary(scene);
    print_textures_summary(scene);
    print_mediums_summary(scene);
    print_triangle_mesh_summary(scene);
  }


  static void print_accelerator(const Accelerator* accel)
  {
    const char* accelTypes[] = { "bvh", "kdtree" };
    printf("==== Accelerator [%s] ====\n", lookup(accelTypes, accel->type()));
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
    printf("==== Camera [%s] ====\n", lookup(cameraTypes, camera->type()));
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
    printf("==== Film [%s] ====\n", lookup(filmTypes, film->type()));
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
    printf("==== Filter [%s] ====\n", lookup(filterTypes, filter->type()));
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
    static const char* integratorTypes[] = { "bdpt", "directlighting", "mlt", "path", "sppm", "whitted", "volpath", "ambientocclusion", nullptr };
    static const char* lightSampleStrategies[] = { "uniform", "power", "spatial", nullptr };
    static const char* directLightSampleStrategies[] = { "uniform", "power", "spatial", nullptr };

    printf("==== Integrator [%s] ====\n", lookup(integratorTypes, integrator->type()));
    switch (integrator->type()) {
    case IntegratorType::BDPT:
      {
        const BDPTIntegrator* typed = dynamic_cast<const BDPTIntegrator*>(integrator);
        printf("maxdepth            = %d\n", typed->maxdepth);
        printf("pixelbounds         = [ %d, %d, %d, %d ]\n", typed->pixelbounds[0], typed->pixelbounds[1], typed->pixelbounds[2], typed->pixelbounds[3]);
        printf("lightsamplestrategy = %s\n", lookup(lightSampleStrategies, typed->lightsamplestrategy));
        printf("visualizestrategies = %s\n", typed->visualizestrategies ? "true" : "false");
        printf("visualizeweights    = %s\n", typed->visualizeweights ? "true" : "false");
      }
      break;
    case IntegratorType::DirectLighting:
      {
        const DirectLightingIntegrator* typed = dynamic_cast<const DirectLightingIntegrator*>(integrator);
        printf("strategy    = %s\n", lookup(directLightSampleStrategies, typed->strategy));
        printf("maxdepth    = %d\n", typed->maxdepth);
        printf("pixelbounds = [ %d, %d, %d, %d ]\n", typed->pixelbounds[0], typed->pixelbounds[1], typed->pixelbounds[2], typed->pixelbounds[3]);
      }
      break;
    case IntegratorType::MLT:
      {
        const MLTIntegrator* typed = dynamic_cast<const MLTIntegrator*>(integrator);
        printf("maxdepth           = %d\n", typed->maxdepth);
        printf("bootstrapsamples   = %d\n", typed->bootstrapsamples);
        printf("chains             = %d\n", typed->chains);
        printf("mutationsperpixel  = %d\n", typed->mutationsperpixel);
        printf("largestprobability = %f\n", typed->largestprobability);
        printf("sigma              = %f\n", typed->sigma);
      }
      break;
    case IntegratorType::Path:
      {
        const PathIntegrator* typed = dynamic_cast<const PathIntegrator*>(integrator);
        printf("maxdepth            = %d\n", typed->maxdepth);
        printf("pixelbounds         = [ %d, %d, %d, %d ]\n", typed->pixelbounds[0], typed->pixelbounds[1], typed->pixelbounds[2], typed->pixelbounds[3]);
        printf("rrthreshold         = %f\n", typed->rrthreshold);
        printf("lightsamplestrategy = %s\n", lookup(lightSampleStrategies, typed->lightsamplestrategy));
      }
      break;
    case IntegratorType::SPPM:
      {
        const SPPMIntegrator* typed = dynamic_cast<const SPPMIntegrator*>(integrator);
        printf("maxdepth           = %d\n", typed->maxdepth);
        printf("maxiterations       = %d\n", typed->maxiterations);
        printf("photonsperiteration = %d\n", typed->photonsperiteration);
        printf("imagewritefrequency = %d\n", typed->imagewritefrequency);
        printf("radius              = %f\n", typed->radius);
      }
      break;
    case IntegratorType::Whitted:
      {
        const WhittedIntegrator* typed = dynamic_cast<const WhittedIntegrator*>(integrator);
        printf("maxdepth            = %d\n", typed->maxdepth);
        printf("pixelbounds         = [ %d, %d, %d, %d ]\n", typed->pixelbounds[0], typed->pixelbounds[1], typed->pixelbounds[2], typed->pixelbounds[3]);
      }
      break;
    case IntegratorType::VolPath:
      {
        const VolPathIntegrator* typed = dynamic_cast<const VolPathIntegrator*>(integrator);
        printf("maxdepth            = %d\n", typed->maxdepth);
        printf("pixelbounds         = [ %d, %d, %d, %d ]\n", typed->pixelbounds[0], typed->pixelbounds[1], typed->pixelbounds[2], typed->pixelbounds[3]);
        printf("rrthreshold         = %f\n", typed->rrthreshold);
        printf("lightsamplestrategy = %s\n", lookup(lightSampleStrategies, typed->lightsamplestrategy));
      }
      break;
    case IntegratorType::AO:
      {
        const AOIntegrator* typed = dynamic_cast<const AOIntegrator*>(integrator);
        printf("pixelbounds = [ %d, %d, %d, %d ]\n", typed->pixelbounds[0], typed->pixelbounds[1], typed->pixelbounds[2], typed->pixelbounds[3]);
        printf("cossample   = %s\n", typed->cossample ? "true" : "false");
        printf("nsamples    = %d\n", typed->nsamples);
      }
      break;
    }

    printf("\n");
  }


  static void print_sampler(const Sampler* sampler)
  {
    static const char* samplerTypes[] = { "02sequence", "lowdiscrepancy", "halton", "maxmindist", "random", "sobol", "stratified", nullptr };

    printf("==== Sampler [%s] ====\n", lookup(samplerTypes, sampler->type()));
    switch (sampler->type()) {
    case SamplerType::ZeroTwoSequence:
    case SamplerType::LowDiscrepancy:
      {
        const ZeroTwoSequenceSampler* typed = dynamic_cast<const ZeroTwoSequenceSampler*>(sampler);
        printf("pixelsamples = %d\n", typed->pixelsamples);
      }
      break;
    case SamplerType::Halton:
      {
        const HaltonSampler* typed = dynamic_cast<const HaltonSampler*>(sampler);
        printf("pixelsamples = %d\n", typed->pixelsamples);
      }
      break;
    case SamplerType::MaxMinDist:
      {
        const MaxMinDistSampler* typed = dynamic_cast<const MaxMinDistSampler*>(sampler);
        printf("pixelsamples = %d\n", typed->pixelsamples);
      }
      break;
    case SamplerType::Random:
      {
        const RandomSampler* typed = dynamic_cast<const RandomSampler*>(sampler);
        printf("pixelsamples = %d\n", typed->pixelsamples);
      }
      break;
    case SamplerType::Sobol:
      {
        const SobolSampler* typed = dynamic_cast<const SobolSampler*>(sampler);
        printf("pixelsamples = %d\n", typed->pixelsamples);
      }
      break;
    case SamplerType::Stratified:
      {
        const StratifiedSampler* typed = dynamic_cast<const StratifiedSampler*>(sampler);
        printf("jitter   = %s\n", typed->jitter ? "true" : "false");
        printf("xsamples = %d\n", typed->xsamples);
        printf("ysamples = %d\n", typed->ysamples);
      }
      break;
    }

    printf("\n");
  }


  static void print_world_summary(const Scene* scene)
  {
    constexpr uint32_t N = 8;
    uint32_t counts[N] = {
      static_cast<uint32_t>(scene->shapes.size()),
      static_cast<uint32_t>(scene->objects.size()),
      static_cast<uint32_t>(scene->instances.size()),
      static_cast<uint32_t>(scene->lights.size()),
      static_cast<uint32_t>(scene->areaLights.size()),
      static_cast<uint32_t>(scene->materials.size()),
      static_cast<uint32_t>(scene->textures.size()),
      static_cast<uint32_t>(scene->mediums.size()),
    };
    const char* names[N] = {
      "shapes",
      "objects",
      "instances",
      "lights",
      "area lights",
      "materials",
      "textures",
      "mediums",
    };
    printf("==== World Summary ====\n");
    print_histogram(N, counts, names);
  }


  static void print_shapes_summary(const Scene* scene)
  {
    if (scene->shapes.empty()) {
      return;
    }
    constexpr uint32_t N = static_cast<uint32_t>(ShapeType::PLYMesh) + 1;
    const char* names[] = { "cones", "curves", "cylinders", "disks", "hyperboloids", "paraboloids", "spheres", "trianglemeshes", "heightfields", "loopsubdivs", "nurbses", "plymeshes", nullptr };
    printf("==== Shape Types ====\n");
    print_histogram_by_type<Shape, N>(scene->shapes, names);
  }


  static void print_lights_summary(const Scene* scene)
  {

    if (scene->lights.empty()) {
      return;
    }
    constexpr uint32_t N = static_cast<uint32_t>(LightType::Spot) + 1;
    const char* names[] = { "distant", "goniometric", "infinite", "point", "projection", "spot", nullptr };
    printf("==== Light Types ====\n");
    print_histogram_by_type<Light, N>(scene->lights, names);
  }


  static void print_area_lights_summary(const Scene* scene)
  {
    if (scene->areaLights.empty()) {
      return;
    }
    constexpr uint32_t N = static_cast<uint32_t>(AreaLightType::Diffuse) + 1;
    const char* names[] = { "diffuse", nullptr };
    printf("==== Area Light Types ====\n");
    print_histogram_by_type<AreaLight, N>(scene->areaLights, names);
  }


  static void print_materials_summary(const Scene* scene)
  {
    if (scene->materials.empty()) {
      return;
    }
    constexpr uint32_t N = static_cast<uint32_t>(MaterialType::Uber) + 1;
    const char* names[] = { "disney", "fourier", "glass", "hair", "kdsubsurface", "matte", "metal", "mirror", "mix", "none", "plastic", "substrate", "subsurface", "translucent", "uber", nullptr };
    printf("==== Material Types ====\n");
    print_histogram_by_type<Material, N>(scene->materials, names);
  }


  static void print_textures_summary(const Scene* scene)
  {
    if (scene->textures.empty()) {
      return;
    }
    constexpr uint32_t N = static_cast<uint32_t>(TextureType::PTex) + 1;
    const char* names[] = { "bilerp", "checkerboard", "constant", "dots", "fbm", "imagemap", "marble", "mix", "scale", "uv", "windy", "wrinkled", "ptex", nullptr };
    printf("==== Texture Types ====\n");
    print_histogram_by_type<Texture, N>(scene->textures, names);
  }


  static void print_mediums_summary(const Scene* scene)
  {
    if (scene->mediums.empty()) {
      return;
    }
    constexpr uint32_t N = static_cast<uint32_t>(MediumType::Heterogeneous) + 1;
    const char* names[] = { "homogeneous", "heterogeneous", nullptr };
    printf("==== Medium Types ====\n");
    print_histogram_by_type<Medium, N>(scene->mediums, names);
  }


  static void print_triangle_mesh_summary(const Scene* scene)
  {
    uint32_t numMeshes = 0;

    uint64_t totalTris = 0;
    uint64_t totalVerts = 0;
    uint64_t totalBytes = 0;

    std::vector<uint32_t> vertCounts;
    std::vector<uint32_t> triCounts;
    std::vector<uint64_t> byteCounts;

    vertCounts.reserve(scene->shapes.size());
    triCounts.reserve(scene->shapes.size());
    byteCounts.reserve(scene->shapes.size());

    for (size_t i = 0, endI = scene->shapes.size(); i < endI; i++) {
      if (scene->shapes[i]->type() != ShapeType::TriangleMesh) {
        continue;
      }

      ++numMeshes;

      const TriangleMesh* trimesh = dynamic_cast<const TriangleMesh*>(scene->shapes[i]);
      uint32_t meshTris = trimesh->num_indices / 3;
      uint64_t meshBytes = triangle_mesh_bytes(trimesh);

      totalTris += meshTris;
      totalVerts += trimesh->num_vertices;
      totalBytes += meshBytes;

      vertCounts.push_back(trimesh->num_vertices);
      triCounts.push_back(meshTris);
      byteCounts.push_back(meshBytes);
    }

    if (numMeshes == 0) {
      return;
    }

    if (numMeshes > 1) {
      std::sort(triCounts.begin(), triCounts.end());
      std::sort(vertCounts.begin(), vertCounts.end());
      std::sort(byteCounts.begin(), byteCounts.end());
    }

    const uint32_t kPrefixCounts = 5;
    const uint32_t kSuffixCounts = kPrefixCounts;
    bool abbreviate = (numMeshes > (kPrefixCounts + kSuffixCounts + 1));

    printf("==== Triangle Mesh Info ====\n");
    printf("\n");

    uint32_t countDigits = uint32_t(ceil(log10(double(triCounts.back()))));
    printf("Triangle counts:\n");
    printf("- Min:    %*u\n", countDigits, triCounts.front());
    printf("- Max:    %*u\n", countDigits, triCounts.back());
    printf("- Median: %*u\n", countDigits, triCounts[numMeshes / 2]);
    printf("- Mean:   %*.1lf\n", countDigits + 2, double(totalTris) / double(numMeshes));
    printf("- Counts:\n");
    if (abbreviate) {
      for (uint32_t i = 0; i < kPrefixCounts; i++) {
        printf("    %*u\n", countDigits, triCounts[i]);
      }
      printf("    %*s\n", countDigits, "...");
      for (uint32_t i = numMeshes - kSuffixCounts; i < numMeshes; i++) {
        printf("    %*u\n", countDigits, triCounts[i]);
      }
    }
    else {
      for (uint32_t count : triCounts) {
        printf("    %*u\n", countDigits, count);
      }
    }
    printf("\n");

    countDigits = uint32_t(ceil(log10(double(vertCounts.back()))));
    printf("Vertex counts:\n");
    printf("- Min:    %*u\n", countDigits, vertCounts.front());
    printf("- Max:    %*u\n", countDigits, vertCounts.back());
    printf("- Median: %*u\n", countDigits, vertCounts[numMeshes / 2]);
    printf("- Mean:   %*.1lf\n", countDigits + 2, double(totalVerts) / double(numMeshes));
    printf("- Counts:\n");
    if (abbreviate) {
      for (uint32_t i = 0; i < kPrefixCounts; i++) {
        printf("    %*u\n", countDigits, vertCounts[i]);
      }
      printf("    %*s\n", countDigits, "...");
      for (uint32_t i = numMeshes - kSuffixCounts; i < numMeshes; i++) {
        printf("    %*u\n", countDigits, vertCounts[i]);
      }
    }
    else {
      for (uint32_t count : vertCounts) {
        printf("    %*u\n", countDigits, count);
      }
    }
    printf("\n");
  }


  static uint64_t triangle_mesh_bytes(const TriangleMesh* trimesh)
  {
    uint64_t meshBytes = trimesh->num_indices * sizeof(int) +
                         trimesh->num_vertices * sizeof(int) * 3;
    if (trimesh->N != nullptr) {
      meshBytes += trimesh->num_vertices * sizeof(int) * 3;
    }
    if (trimesh->S != nullptr) {
      meshBytes += trimesh->num_vertices * sizeof(int) * 3;
    }
    if (trimesh->uv != nullptr) {
      meshBytes += trimesh->num_vertices * sizeof(int) * 2;
    }
    return meshBytes;
  }

} // namespace minipbrt


static bool has_extension(const char* filename, const char* ext)
{
  int j = int(strlen(ext));
  int i = int(strlen(filename)) - j;
  if (i <= 0 || filename[i - 1] != '.') {
    return false;
  }
  return strcmp(filename + i, ext) == 0;
}


int main(int argc, char** argv)
{
  const int kFilenameBufferLen = 16 * 1024 - 1;
  char* filenameBuffer = new char[kFilenameBufferLen + 1];
  filenameBuffer[kFilenameBufferLen] = '\0';

  std::vector<std::string> filenames;
  for (int i = 1; i < argc; i++) {
    if (has_extension(argv[i], "txt")) {
      FILE* f = fopen(argv[i], "r");
      if (f != nullptr) {
        while (fgets(filenameBuffer, kFilenameBufferLen, f)) {
          filenames.push_back(filenameBuffer);
          while (filenames.back().back() == '\n') {
            filenames.back().pop_back();
          }
        }
        fclose(f);
      }
      else {
        fprintf(stderr, "Failed to open %s\n", argv[i]);
      }
    }
    else {
      filenames.push_back(argv[i]);
    }
  }

  if (filenames.empty()) {
    fprintf(stderr, "No input files provided.\n");
    return EXIT_SUCCESS;
  }
  else if (filenames.size() == 1) {
    minipbrt::Parser parser;
    bool ok = parser.parse(filenames.front().c_str());
    bool plyOK = ok ? parser.borrow_scene()->load_all_ply_meshes() : false;

    if (!ok) {
      minipbrt::print_error(parser.get_error());
      return EXIT_FAILURE;
    }
    else if (!plyOK) {
      fprintf(stderr, "[%s] Failed to load ply meshes.\n", filenames.front().c_str());
      return EXIT_FAILURE;
    }
    else {
      minipbrt::print_scene_info(parser.borrow_scene());
      return EXIT_SUCCESS;
    }
  }
  else {
    int width = 0;
    for (const std::string& filename : filenames) {
      int newWidth = int(filename.size());
      if (newWidth > width) {
        width = newWidth;
      }
    }

    int numPassed = 0;
    int numFailed = 0;
    for (const std::string& filename : filenames) {
      minipbrt::Parser parser;
      bool ok = parser.parse(filename.c_str());
      bool plyOK = ok ? parser.borrow_scene()->load_all_ply_meshes() : false;
      printf("%-*s  %s", width, filename.c_str(), (ok && plyOK) ? "passed" : "FAILED");
      if (!ok) {
        const minipbrt::Error* err = parser.get_error();
        printf(" ---> [%s, line %lld, column %lld] %s\n", err->filename(), err->line(), err->column(), err->message());
        ++numFailed;
      }
      else if (!plyOK) {
        printf(" ---> Failed to load ply meshes\n");
        ++numFailed;
      }
      else {
        printf("\n");
        ++numPassed;
      }
      fflush(stdout);
    }
    printf("----\n");
    printf("%d passed\n", numPassed);
    printf("%d failed\n", numFailed);
    return (numFailed > 0) ? EXIT_FAILURE : EXIT_SUCCESS;
  }
}
