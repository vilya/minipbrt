Performance
===========

Test hardware used
------------------

The laptop used for the results below was:

- Windows 10, v1903
- Intel Core i7-6700HQ CPU, 2.6 GHz
- 16 GB Dual-channel DDR4 RAM
- Samsung MZVPV512 SSD, theoretical peak read speed of 1165 MB/s

All times reported below are in seconds. 

The times include parsing the PBRT files, constructing the scene
representation and loading any PLY files referenced by it. They do not include
the time taken to destroy the scene representation.

I used a minipbrt binary compiled with CMake's default Release Build
settings using Visual Studio 2019.


Results for all scenes in pbrt-v3-scenes
----------------------------------------

Source: https://www.pbrt.org/scenes-v3.html

| Scene                                            | Parsed OK? | Time       |
| :----------------------------------------------: | :--------: | ---------: |
| barcelona-pavilion/pavilion-day.pbrt             | passed     | 0.617 secs |
| barcelona-pavilion/pavilion-night.pbrt           | passed     | 0.608 secs |
| bathroom/bathroom.pbrt                           | passed     | 0.055 secs |
| bmw-m6/bmw-m6.pbrt                               | passed     | 0.070 secs |
| breakfast/breakfast.pbrt                         | passed     | 0.030 secs |
| breakfast/breakfast-lamps.pbrt                   | passed     | 0.028 secs |
| breakfast/f16-8a.pbrt                            | passed     | 0.028 secs |
| breakfast/f16-8b.pbrt                            | passed     | 0.030 secs |
| buddha-fractal/buddha-fractal.pbrt               | passed     | 0.028 secs |
| bunny-fur/f3-15.pbrt                             | passed     | 1.976 secs |
| caustic-glass/f16-11a.pbrt                       | passed     | 0.026 secs |
| caustic-glass/f16-11b.pbrt                       | passed     | 0.011 secs |
| caustic-glass/f16-9a.pbrt                        | passed     | 0.011 secs |
| caustic-glass/f16-9b.pbrt                        | passed     | 0.011 secs |
| caustic-glass/f16-9c.pbrt                        | passed     | 0.012 secs |
| caustic-glass/glass.pbrt                         | passed     | 0.012 secs |
| chopper-titan/chopper-titan.pbrt                 | passed     | 2.244 secs |
| cloud/cloud.pbrt                                 | passed     | 0.028 secs |
| cloud/f15-4a.pbrt                                | passed     | 0.016 secs |
| cloud/f15-4b.pbrt                                | passed     | 0.017 secs |
| cloud/f15-4c.pbrt                                | passed     | 0.017 secs |
| cloud/smoke.pbrt                                 | passed     | 0.016 secs |
| coffee-splash/f15-5.pbrt                         | passed     | 0.103 secs |
| coffee-splash/splash.pbrt                        | passed     | 0.023 secs |
| contemporary-bathroom/contemporary-bathroom.pbrt | passed     | 0.092 secs |
| crown/crown.pbrt                                 | passed     | 4.443 secs |
| dambreak/dambreak0.pbrt                          | passed     | 0.196 secs |
| dambreak/dambreak1.pbrt                          | passed     | 0.255 secs |
| dragon/f11-13.pbrt                               | passed     | 0.391 secs |
| dragon/f11-14.pbrt                               | passed     | 0.364 secs |
| dragon/f14-3.pbrt                                | passed     | 0.190 secs |
| dragon/f14-5.pbrt                                | passed     | 0.363 secs |
| dragon/f15-13.pbrt                               | passed     | 0.364 secs |
| dragon/f8-10.pbrt                                | passed     | 0.187 secs |
| dragon/f8-14a.pbrt                               | passed     | 0.191 secs |
| dragon/f8-14b.pbrt                               | passed     | 0.186 secs |
| dragon/f8-21a.pbrt                               | passed     | 0.187 secs |
| dragon/f8-21b.pbrt                               | passed     | 0.188 secs |
| dragon/f8-24.pbrt                                | passed     | 0.363 secs |
| dragon/f8-4a.pbrt                                | passed     | 0.187 secs |
| dragon/f8-4b.pbrt                                | passed     | 0.185 secs |
| dragon/f9-3.pbrt                                 | passed     | 0.186 secs |
| dragon/f9-4.pbrt                                 | passed     | 0.188 secs |
| ecosys/ecosys.pbrt                               | passed     | 0.173 secs |
| figures/f10-1ac.pbrt                             | passed     | 0.006 secs |
| figures/f10-1b.pbrt                              | passed     | 0.005 secs |
| figures/f11-15.pbrt                              | passed     | 0.004 secs |
| figures/f3-18.pbrt                               | passed     | 0.005 secs |
| figures/f7-19a.pbrt                              | passed     | 0.005 secs |
| figures/f7-19b.pbrt                              | passed     | 0.005 secs |
| figures/f7-19c.pbrt                              | passed     | 0.005 secs |
| figures/f7-30a.pbrt                              | passed     | 0.005 secs |
| figures/f7-30b.pbrt                              | passed     | 0.005 secs |
| figures/f7-30c.pbrt                              | passed     | 0.006 secs |
| figures/f7-34a.pbrt                              | passed     | 0.005 secs |
| figures/f7-34b.pbrt                              | passed     | 0.004 secs |
| figures/f7-34c.pbrt                              | passed     | 0.005 secs |
| figures/f8-22.pbrt                               | passed     | 0.009 secs |
| ganesha/f3-11.pbrt                               | passed     | 0.515 secs |
| ganesha/ganesha.pbrt                             | passed     | 0.442 secs |
| hair/curly-hair.pbrt                             | passed     | 4.712 secs |
| hair/sphere-hairblock.pbrt                       | passed     | 0.025 secs |
| hair/straight-hair.pbrt                          | passed     | 1.718 secs |
| head/f9-5.pbrt                                   | passed     | 0.017 secs |
| head/head.pbrt                                   | passed     | 0.008 secs |
| killeroos/killeroo-gold.pbrt                     | passed     | 0.061 secs |
| killeroos/killeroo-moving.pbrt                   | passed     | 0.051 secs |
| killeroos/killeroo-simple.pbrt                   | passed     | 0.009 secs |
| landscape/f4-1.pbrt                              | passed     | 6.439 secs |
| landscape/f6-13.pbrt                             | passed     | 3.561 secs |
| landscape/f6-14.pbrt                             | passed     | 3.546 secs |
| landscape/view-0.pbrt                            | passed     | 3.563 secs |
| landscape/view-1.pbrt                            | passed     | 3.586 secs |
| landscape/view-2.pbrt                            | passed     | 3.519 secs |
| landscape/view-3.pbrt                            | passed     | 3.545 secs |
| landscape/view-4.pbrt                            | passed     | 3.511 secs |
| lte-orb/lte-orb-roughglass.pbrt                  | passed     | 0.052 secs |
| lte-orb/lte-orb-silver.pbrt                      | passed     | 0.046 secs |
| measure-one/frame120.pbrt                        | passed     | 8.163 secs |
| measure-one/frame180.pbrt                        | passed     | 1.156 secs |
| measure-one/frame210.pbrt                        | passed     | 1.099 secs |
| measure-one/frame25.pbrt                         | passed     | 1.047 secs |
| measure-one/frame300.pbrt                        | passed     | 1.129 secs |
| measure-one/frame35.pbrt                         | passed     | 1.127 secs |
| measure-one/frame380.pbrt                        | passed     | 1.028 secs |
| measure-one/frame52.pbrt                         | passed     | 1.239 secs |
| measure-one/frame85.pbrt                         | passed     | 1.018 secs |
| pbrt-book/book.pbrt                              | passed     | 0.027 secs |
| sanmiguel/f10-8.pbrt                             | passed     | 6.190 secs |
| sanmiguel/f16-21a.pbrt                           | passed     | 0.795 secs |
| sanmiguel/f16-21b.pbrt                           | passed     | 0.791 secs |
| sanmiguel/f16-21c.pbrt                           | passed     | 0.801 secs |
| sanmiguel/f6-17.pbrt                             | passed     | 0.902 secs |
| sanmiguel/f6-25.pbrt                             | passed     | 0.813 secs |
| sanmiguel/sanmiguel.pbrt                         | passed     | 0.813 secs |
| sanmiguel/sanmiguel_cam1.pbrt                    | passed     | 0.790 secs |
| sanmiguel/sanmiguel_cam14.pbrt                   | passed     | 0.712 secs |
| sanmiguel/sanmiguel_cam15.pbrt                   | passed     | 0.674 secs |
| sanmiguel/sanmiguel_cam18.pbrt                   | passed     | 0.894 secs |
| sanmiguel/sanmiguel_cam20.pbrt                   | passed     | 0.812 secs |
| sanmiguel/sanmiguel_cam25.pbrt                   | passed     | 0.805 secs |
| sanmiguel/sanmiguel_cam3.pbrt                    | passed     | 0.803 secs |
| sanmiguel/sanmiguel_cam4.pbrt                    | passed     | 0.812 secs |
| simple/anim-bluespheres.pbrt                     | passed     | 0.007 secs |
| simple/buddha.pbrt                               | passed     | 0.117 secs |
| simple/bump-sphere.pbrt                          | passed     | 0.005 secs |
| simple/caustic-proj.pbrt                         | passed     | 0.004 secs |
| simple/dof-dragons.pbrt                          | passed     | 0.334 secs |
| simple/miscquads.pbrt                            | passed     | 0.005 secs |
| simple/room-mlt.pbrt                             | passed     | 0.028 secs |
| simple/room-path.pbrt                            | passed     | 0.016 secs |
| simple/room-sppm.pbrt                            | passed     | 0.017 secs |
| simple/spheres-differentials-texfilt.pbrt        | passed     | 0.006 secs |
| simple/spotfog.pbrt                              | passed     | 0.005 secs |
| simple/teapot-area-light.pbrt                    | passed     | 0.011 secs |
| simple/teapot-metal.pbrt                         | passed     | 0.013 secs |
| smoke-plume/plume-084.pbrt                       | passed     | 0.290 secs |
| smoke-plume/plume-184.pbrt                       | passed     | 0.329 secs |
| smoke-plume/plume-284.pbrt                       | passed     | 0.347 secs |
| sportscar/f12-19a.pbrt                           | passed     | 0.917 secs |
| sportscar/f12-19b.pbrt                           | passed     | 0.628 secs |
| sportscar/f12-20a.pbrt                           | passed     | 0.624 secs |
| sportscar/f12-20b.pbrt                           | passed     | 0.622 secs |
| sportscar/f7-37a.pbrt                            | passed     | 0.627 secs |
| sportscar/f7-37b.pbrt                            | passed     | 0.621 secs |
| sportscar/sportscar.pbrt                         | passed     | 0.619 secs |
| sssdragon/dragon_10.pbrt                         | passed     | 1.112 secs |
| sssdragon/dragon_250.pbrt                        | passed     | 0.982 secs |
| sssdragon/dragon_50.pbrt                         | passed     | 0.990 secs |
| sssdragon/f15-7.pbrt                             | passed     | 0.998 secs |
| structuresynth/arcsphere.pbrt                    | passed     | 0.024 secs |
| structuresynth/ballpile.pbrt                     | passed     | 0.014 secs |
| structuresynth/metal.pbrt                        | passed     | 0.025 secs |
| structuresynth/microcity.pbrt                    | passed     | 0.032 secs |
| transparent-machines/frame1266.pbrt              | passed     | 5.404 secs |
| transparent-machines/frame542.pbrt               | passed     | 1.844 secs |
| transparent-machines/frame675.pbrt               | passed     | 2.507 secs |
| transparent-machines/frame812.pbrt               | passed     | 3.108 secs |
| transparent-machines/frame888.pbrt               | passed     | 3.962 secs |
| tt/tt.pbrt                                       | passed     | 1.888 secs |
| veach-bidir/bidir.pbrt                           | passed     | 0.084 secs |
| veach-mis/mis.pbrt                               | passed     | 0.027 secs |
| villa/f16-20a.pbrt                               | passed     | 2.231 secs |
| villa/f16-20b.pbrt                               | passed     | 0.393 secs |
| villa/f16-20c.pbrt                               | passed     | 0.380 secs |
| villa/villa-daylight.pbrt                        | passed     | 0.387 secs |
| villa/villa-lights-on.pbrt                       | passed     | 0.395 secs |
| villa/villa-photons.pbrt                         | passed     | 0.382 secs |
| volume-caustic/caustic.pbrt                      | passed     | 0.007 secs |
| volume-caustic/f16-22a.pbrt                      | passed     | 0.005 secs |
| volume-caustic/f16-22b.pbrt                      | passed     | 0.005 secs |
| vw-van/vw-van.pbrt                               | passed     | 1.036 secs |
| white-room/whiteroom-daytime.pbrt                | passed     | 1.160 secs |
| white-room/whiteroom-night.pbrt                  | passed     | 0.106 secs |
| yeahright/yeahright.pbrt                         | passed     | 0.034 secs |

132.442 secs total
155 passed
0 failed


Results for all scenes in Benedikt Bitterli's collection
--------------------------------------------------------

Source: https://benedikt-bitterli.me/resources/

| Scene                           | Parsed OK? | Time       |
| :-----------------------------: | :--------: | ---------: |
| ./bathroom/scene.pbrt           | passed     | 4.837 secs |
| ./bathroom2/scene.pbrt          | passed     | 0.731 secs |
| ./bedroom/scene.pbrt            | passed     | 0.994 secs |
| ./car/scene.pbrt                | passed     | 0.069 secs |
| ./car2/scene.pbrt               | passed     | 0.082 secs |
| ./classroom/scene.pbrt          | passed     | 0.402 secs |
| ./coffee/scene.pbrt             | passed     | 0.020 secs |
| ./cornell-box/scene.pbrt        | passed     | 0.006 secs |
| ./curly-hair/scene.pbrt         | passed     | 6.029 secs |
| ./dining-room/scene.pbrt        | passed     | 0.351 secs |
| ./dragon/scene.pbrt             | passed     | 0.279 secs |
| ./furball/scene.pbrt            | passed     | 6.456 secs |
| ./glass-of-water/scene.pbrt     | passed     | 0.239 secs |
| ./hair-curl/scene.pbrt          | passed     | 5.942 secs |
| ./house/scene.pbrt              | passed     | 2.584 secs |
| ./kitchen/scene.pbrt            | passed     | 2.523 secs |
| ./lamp/scene.pbrt               | passed     | 0.187 secs |
| ./living-room/scene.pbrt        | passed     | 0.596 secs |
| ./living-room-2/scene.pbrt      | passed     | 1.551 secs |
| ./living-room-3/scene.pbrt      | passed     | 1.610 secs |
| ./material-testball/scene.pbrt  | passed     | 0.082 secs |
| ./spaceship/scene.pbrt          | passed     | 0.215 secs |
| ./staircase/scene.pbrt          | passed     | 4.470 secs |
| ./staircase2/scene.pbrt         | passed     | 0.163 secs |
| ./straight-hair/scene.pbrt      | passed     | 3.114 secs |
| ./teapot/scene.pbrt             | passed     | 0.079 secs |
| ./teapot-full/scene.pbrt        | passed     | 0.095 secs |
| ./veach-ajar/scene.pbrt         | passed     | 0.449 secs |
| ./veach-bidir/scene.pbrt        | passed     | 0.085 secs |
| ./veach-mis/scene.pbrt          | passed     | 0.006 secs |
| ./volumetric-caustic/scene.pbrt | passed     | 0.005 secs |
| ./water-caustic/scene.pbrt      | passed     | 0.066 secs |

47.744 secs total
32 passed
0 failed


Results for Disney's Moana island scene
---------------------------------------

Source: https://www.technology.disneyanimation.com/islandscene

| Scene                           | Parsed OK? | Time         |
| :-----------------------------: | :--------: | -----------: |
| ./pbrt/island.pbrt              | passed     | 137.763 secs |
| ./pbrt/islandX.pbrt             | passed     | 140.141 secs |

322.364 secs total
2 passed
0 failed
