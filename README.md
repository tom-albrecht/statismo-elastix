statismo-elastix
================

An external component for the elastix registration software that uses the statismo library for statistical shape model based registration.

Prerequisites
------------

You need to download and compile elastix and statismo. Both necessitate an installation of ITK.
We tested statismo-elastix with elastix 4.6 and statismo 0.9.

You need a statistical deformation model in statismo's hdf5 file format. While it is possible to 
build this model using registration results generated with elastix, this statismo-elastix software
does not provide this functionality. The model needs to be suited to your registration task and 
aligned with your registration target.


Installation
-----------

statismo-elastix is built as an elastix "user component" from within the cmake build of elastix. 
To point cmake to the code, you need to add the statismo-elastix directory to the cmake variable 
ELASTIX_USER_COMPONENT_DIRS. If you already have other user components, the variable can hold
multiple directories, separated by a semicolon (;).

After running cmake's configure routine once, cmake will demand the location of the statismo 
directory. This is the installation directory of your statismo library. After this is specified,
you should be able to run configure, generate, build and install elastix with cmake. This will
add the transform SimpleStatisticalDeformationModelTransform to your elastix installation.


Usage
-----

In order to use the new transform, you need to specify the line:

(Transform "SimpleStatisticalDeformationModelTransform")

in your elastix parameter file, replacing any other transforms you may have been using.

The path to your statistical shape model is specified in this way:

(StatisticalModelName "/path/to/your/model.h5")


Extending statismo-elastix
-----------------------

The transform is named SimpleStatisticalDeformationModelTransform because it demonstrates the
most simple cooperation of statismo and elastix. Many extensions, taking advantage of additional
features of statismo and elastix can be imagined, for instance, the use of landmarks, posterior 
models, automatic initialization, multi-resolution, intensity model-based metrics to name a few. 

If you wish to extend statismo-elastix, you can create a new subdirectory of statismo-elastix 
and, most likely starting from the code for the SimpleStatisticalDeformationModelTransform, 
write your own elastix user component. When you are ready to share it with the community, you 
can send a pull request via github to make it part of the official statismo-elastix repository.






