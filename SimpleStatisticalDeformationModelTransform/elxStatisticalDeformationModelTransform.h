/*======================================================================

  This file is part of the elastix software.
  This file is part of the statismo software.

	Copyright (c) University of Basel. All rights reserved.
  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/

#ifndef __elxStatisticalDeformationModelTransform_H_
#define __elxStatisticalDeformationModelTransform_H_
#include "itkAdvancedStatisticalDeformationModelTransform.h"


#include "itkStatisticalModel.h"
#include "itkStandardImageRepresenter.h"

#include "elxIncludes.h"
#include "itkImage.h"
#include "itkVector.h"
#include <vector>

namespace elastix
{

  /**
   * \class SimpleStatisticalDeformationModelTransformElastix
   * \brief A transform based on the itk::StatisticalDeformationModelTransform.
   *
   * This is a transform based on a statistical deformation model.
   * A linear combination of deformation fields defines the transformation of points.
   * A statistical shape model needs to be specified.
   * In addition, a set of source and target landmarks can be specified, which are used to
   * constrain the model to adhere to these landmarks. \n
   * A certain amount of slack or noise is assumed in the landmark placement. This can be
   * specified. Because the landmarks are typically defined on a surface, the noise can be
   * specified in normal and tangential direction to this surface, because typically the
   * accuracy is higher in normal than in tangential direction. \n
   *
   * The parameters used in this class are:
   * \parameter Transform: Select this transform as follows:\n
   *    <tt>(%Transform "StatisticalDeformationModelTransform")</tt>
   * \parameter StatisticalModelName: The file name of the statistical deformation
   * 		model to be used. \n
   *    example: <tt>(StatisticalModelName "DeformationModel.h5")</tt> \n
   * \parameter UsedNumberOfStatisticalModelCoefficients: The number of coefficients and
   * 		deformation fields used for the statistical model. Choosing a number lower than the
   * 		amount of deformation fields in the model may speed up the registration, possibly at
   * 		the cost of accuracy. \n
   *    example: <tt>(UsedNumberOfStatisticalModelCoefficients 10)</tt> \n
   *    The default value is 0, which results in all available coefficients to be used.\n

   *
   * \ingroup Transforms
   */

  template < class TElastix >
    class SimpleStatisticalDeformationModelTransformElastix:
      public itk::AdvancedCombinationTransform<
          typename elx::TransformBase<TElastix>::CoordRepType,
          elx::TransformBase<TElastix>::FixedImageDimension > ,
      public elx::TransformBase<TElastix>
  {
  public:

    /** Standard ITK-stuff. */
    typedef SimpleStatisticalDeformationModelTransformElastix                     Self;

    typedef itk::AdvancedCombinationTransform<
      typename elx::TransformBase<TElastix>::CoordRepType,
      elx::TransformBase<TElastix>::FixedImageDimension >   Superclass1;

    typedef elx::TransformBase<TElastix>                    Superclass2;

    typedef itk::SmartPointer<Self>                         Pointer;
    typedef itk::SmartPointer<const Self>                   ConstPointer;

    /** Method for creation through the object factory. */
    itkNewMacro( Self );

    /** Run-time type information (and related methods). */
    itkTypeMacro( SimpleStatisticalDeformationModelTransformElastix, itk::AdvancedCombinationTransform );

    /** Name of this class.
     * Use this name in the parameter file to select this specific transform. \n
     * example: <tt>(Transform "SimpleStatisticalDeformationModelTransform")</tt>\n
     */
    elxClassNameMacro( "SimpleStatisticalDeformationModelTransform" );

    /** Dimension of the domain space. */
    itkStaticConstMacro( SpaceDimension, unsigned int, Superclass2::FixedImageDimension );

    /** Typedefs inherited from the superclass. */
    typedef typename Superclass1::ScalarType                ScalarType;
    typedef typename Superclass1::ParametersType            ParametersType;
    typedef typename Superclass1::JacobianType              JacobianType;
    typedef typename Superclass1::InputVectorType           InputVectorType;
    typedef typename Superclass1::OutputVectorType          OutputVectorType;
    typedef typename Superclass1::InputCovariantVectorType  InputCovariantVectorType;
    typedef typename Superclass1::OutputCovariantVectorType OutputCovariantVectorType;
    typedef typename Superclass1::InputVnlVectorType        InputVnlVectorType;
    typedef typename Superclass1::OutputVnlVectorType       OutputVnlVectorType;
    typedef typename Superclass1::InputPointType            InputPointType;
    typedef typename Superclass1::OutputPointType           OutputPointType;

    /** Typedef's from the TransformBase class. */
    typedef typename Superclass2::ElastixType               ElastixType;
    typedef typename Superclass2::ElastixPointer            ElastixPointer;
    typedef typename Superclass2::ConfigurationType         ConfigurationType;
    typedef typename Superclass2::ConfigurationPointer      ConfigurationPointer;
    typedef typename Superclass2::RegistrationType          RegistrationType;
    typedef typename Superclass2::RegistrationPointer       RegistrationPointer;
    typedef typename Superclass2::CoordRepType              CoordRepType;
    typedef typename Superclass2::FixedImageType            FixedImageType;
    typedef typename Superclass2::MovingImageType           MovingImageType;
    typedef typename Superclass2::ITKBaseType               ITKBaseType;
    typedef typename Superclass2::CombinationTransformType  CombinationTransformType;

    /** Statismo typedefs */
	typedef itk::Vector<CoordRepType, elx::TransformBase<TElastix>::FixedImageDimension> VectorPixelType;
    typedef itk::Image<VectorPixelType, elx::TransformBase<TElastix>::FixedImageDimension> ImageType;
    typedef itk::StandardImageRepresenter<VectorPixelType, elx::TransformBase<TElastix>::FixedImageDimension> RepresenterType;
	typedef itk::StatisticalModel<ImageType> StatisticalModelType;

    /** The ITK-class that provides most of the functionality, and
     * that is set as the "CurrentTransform" in the CombinationTransform */
    typedef itk::AdvancedStatisticalDeformationModelTransform<
      RepresenterType, CoordRepType, elx::TransformBase<TElastix>::FixedImageDimension >   StatisticalDeformationModelTransformType;
    typedef typename StatisticalDeformationModelTransformType::Pointer      StatisticalDeformationModelTransformPointer;

    /** Execute stuff before the actual registration:
     * \li Call InitializeTransform.
     */
    virtual int BeforeAll(void);

    virtual int BeforeAllTransformix(void);

    /** Initialize Transform.
     * \li Set all parameters to zero.
     * \li Set initial translation:
     *  the initial translation between fixed and moving image is guessed,
     *  if the user has set (AutomaticTransformInitialization "true").
     */
    virtual void InitializeTransform(void);

    /** Function to write transform-parameters to a file. */
    virtual void WriteToFile( const ParametersType & param ) const;
    /** Function to write everything specific to this transform to file. */
    virtual void WriteToFileSpecific( const ParametersType & param ) const;


    /** Read a file of landmarks from a file. */
    std::vector<InputPointType> ReadPointSetFromFile( const std::string filename ) const;


    virtual void ComputeJacobianWithRespectToParameters(
      const InputPointType &p, JacobianType &j ) const {
    	this->m_StatisticalDeformationModelTransform->ComputeJacobianWithRespectToParameters(p,j);
    }
    virtual void ComputeJacobianWithRespectToPosition(
      const InputPointType &p, JacobianType &j ) const{
    	this->m_StatisticalDeformationModelTransform->ComputeJacobianWithRespectToPosition(p,j);
    }

  protected:

    /** The constructor. */
    SimpleStatisticalDeformationModelTransformElastix();
    /** The destructor. */
    virtual ~SimpleStatisticalDeformationModelTransformElastix() {};

    StatisticalDeformationModelTransformPointer m_StatisticalDeformationModelTransform;
    typename StatisticalModelType::Pointer m_StatisticalModel;
    std::string m_StatisticalModelName;



  private:

    /** The private constructor. */
    SimpleStatisticalDeformationModelTransformElastix( const Self& ); // purposely not implemented
    /** The private copy constructor. */
    void operator=( const Self& );              // purposely not implemented

  }; // end class SimpleStatisticalDeformationModelTransformElastix


} // end namespace elastix

#ifndef ITK_MANUAL_INSTANTIATION
#include "elxStatisticalDeformationModelTransform.hxx"
#endif

#endif // end #ifndef __elxStatisticalDeformationModelTransform_H_
