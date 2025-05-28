<?php
global $entities;
	  $entities[] = array(
						  'entity'=> array('table'=>'housing_license_application','tableAlias'=>'hla'),
						  'type'=>'Renew License', 
						  'join'=> array('hfo' =>array(
													'joinEntity'=>'housing_occupant_license' ,
												  	'onClause'=> array(
																		'leftEntity'=>'license_application_id',
																		'rightEntity'=>'license_application_id'
																),
													'joinType'=> 'left'
												) 
									),
						
						  'fields'=>array(),
						  'expressions'=>array(),
						  'condition' => array(
											  'hla' =>array(
											  				array(
																'attribute' => 'type_of_application',
																'value' => 'renew',
																'operator' => '='
																)
														   ) 
											  )
						  );