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

#ifndef __elxStatisticalDeformationModelTransform_HXX_
#define __elxStatisticalDeformationModelTransform_HXX_

#include "elxStatisticalDeformationModelTransform.h"
#include <itkTransformixInputPointFileReader.h>
#include <itkOptimizerParameters.h>
#include "itkImageFileWriter.h"
#include "vnl/vnl_copy.h"

#include <itkMeshFileReader.h>
#include <itkPointsLocator.h>

#include <Eigen/QR>

namespace elastix
{

  /**
   * ********************* Constructor ****************************
   */

  template <class TElastix>
    SimpleStatisticalDeformationModelTransformElastix<TElastix>
    ::SimpleStatisticalDeformationModelTransformElastix()
  {
    this->m_StatisticalDeformationModelTransform =
      StatisticalDeformationModelTransformType::New();
    this->SetCurrentTransform( this->m_StatisticalDeformationModelTransform );
  } // end Constructor


  /*
   * ******************* BeforeRegistration ***********************
   */

  template <class TElastix>
    int SimpleStatisticalDeformationModelTransformElastix<TElastix>
    ::BeforeAll(void)
  {
  	/** Give initial parameters to this->m_Registration.*/
    this->InitializeTransform();
    return 0;

  }

  template <class TElastix>
    int SimpleStatisticalDeformationModelTransformElastix<TElastix>
    ::BeforeAllTransformix(void)
  {

  	return this->BeforeAll();

  } // end BeforeAllTransformix


  /**
   * ************************* InitializeTransform *********************
   */

  template <class TElastix>
    void SimpleStatisticalDeformationModelTransformElastix<TElastix>
    ::InitializeTransform( void )
  {

  	std::cout << "InitializeTransform" << std::endl;


  	// Read original statistical model. If no initialization with
  	// point values is performed, this one is used in the registration.
    this->GetConfiguration()->ReadParameter( m_StatisticalModelName,
      "StatisticalModelName", 0);
    typename StatisticalModelType::Pointer statisticalModel = StatisticalModelType::New();

    statisticalModel->Load(m_StatisticalModelName.c_str());

    unsigned usedNumberOfStatisticalModelCoefficients = 0;
    this->GetConfiguration()->ReadParameter( usedNumberOfStatisticalModelCoefficients,  "UsedNumberOfStatisticalModelCoefficients", 0, false);

    if(usedNumberOfStatisticalModelCoefficients > 0) {
    	this->m_StatisticalDeformationModelTransform->SetUsedNumberOfCoefficients(usedNumberOfStatisticalModelCoefficients);
    }

    bool automaticTransformInitialization = false;

		this->m_StatisticalModel = statisticalModel;

		this->m_StatisticalDeformationModelTransform->SetStatisticalModel(m_StatisticalModel);
		this->m_StatisticalDeformationModelTransform->SetIdentity();


    /** Set the initial parameters in this->m_Registration.*/
    if(this->m_Registration)
    	this->m_Registration->GetAsITKBaseType()->
      SetInitialTransformParameters( this->GetParameters() );

  } // end InitializeTransform




  /**
   * ************************* WriteToFile ************************
   *
   * Saves the TransformParameters as a vector and if wanted
   * also as a deformation field.
   */

  template <class TElastix>
  void SimpleStatisticalDeformationModelTransformElastix<TElastix>
  ::WriteToFile( const ParametersType & param ) const
  {
    /** Call the WriteToFile from the TransformBase. */
    this->Superclass2::WriteToFile( param );
    this->WriteToFileSpecific( param );
  }


  /**
   * ************************* WriteToFileSpecific ********************
   *
   * Saves all the stuff specific to this transform
   *
   */
  template <class TElastix>
  void SimpleStatisticalDeformationModelTransformElastix<TElastix>
  ::WriteToFileSpecific( const ParametersType & param ) const
  {

    /** Add some StatisticalDeformationModelTransform specific lines. */
    xout["transpar"] << std::endl << "// StatsisticalDeformationModel specific" << std::endl;

    xout["transpar"] << "(StatisticalModelName \"" << m_StatisticalModelName << "\")" << std::endl;



  } // end WriteToFileSpecific()



} // end namespace elastix


#endif // end #ifndef __elxStatisticalDeformationModelTransform_HXX_

