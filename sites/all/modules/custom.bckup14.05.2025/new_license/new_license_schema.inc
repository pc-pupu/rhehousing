<?php
global $entities;
	  $entities[] = array(
						  'entity'=> array('table'=>'housing_license_application','tableAlias'=>'hla'),
						  'type'=>'New Licence', 
						  'join'=> array('hfo' =>array(
													'joinEntity'=>'housing_flat_occupant' ,
												  	'onClause'=> array(
																		'leftEntity'=>'online_application_id',
																		'rightEntity'=>'online_application_id'
																),
													'joinType'=> 'left'
												) 
									),
						
						'fields'=>array( 'hla'=>array(
										  				'Allotment No'=>array('allotment_no','allotment_no'),
														'Allotment District'=>array('allotment_district','allotment_district'),
														'Allotment Housing'=>array('allotment_estate','allotment_estate'),
														'Allotment Housing Address'=>array('allotment_address','allotment_address'),
														//'Allotment Flat No'=>array('allotment_flat','allotment_flat')
												),
								),
						
						'expressions'=>array('hla'=>array(
														'Allotment Date'=>array("to_char(hla.allotment_date, 'DD/MM/YYYY')",'allotment_date'))),
						  'condition' => array(
											  'hla' =>array(
											  				array(
																'attribute' => 'type_of_application',
																'value' => 'new',
																'operator' => '='
																)
														   ) 
											  )
						  );