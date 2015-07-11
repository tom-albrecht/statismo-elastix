FIND_PACKAGE(STATISMO REQUIRED)
#Force elastix to link also statismo libraries 
set(elxLinkLibs  ${statismo_LIBRARIES}  ${elxLinkLibs}  ) #${Boost_LIBRARIES}
include_directories(${statismo_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ) 
ADD_ELXCOMPONENT( SimpleStatisticalDeformationModelTransformElastix
 itkAdvancedStatisticalDeformationModelTransform.h
 itkAdvancedStatisticalModelTransformBase.h
 itkAdvancedStatisticalModelTransformBase.txx
 elxStatisticalDeformationModelTransform.h
 elxStatisticalDeformationModelTransform.hxx
 elxStatisticalDeformationModelTransform.cxx )

