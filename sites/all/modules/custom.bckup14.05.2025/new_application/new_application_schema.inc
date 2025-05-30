<?php
global $entities;
$entities[] = array(
						  'entity'=> array('table'=>'housing_new_allotment_application','tableAlias'=>'hna'),
						  'type'=>'New Allotment',
						  'join'=> array(
						  				'he1' =>array(
													'joinEntity'=>'housing_estate' ,
													'onClause'=> array(
																		'leftEntity'=>'estate_id_choice1',
																		'rightEntity'=>'estate_id'
																		),
													'joinType'=> 'left'
												  	),
										'he2' =>array(
													'joinEntity'=>'housing_estate' ,
													'onClause'=> array(
																		'leftEntity'=>'estate_id_choice2',
																		'rightEntity'=>'estate_id'
																		),
													'joinType'=> 'left'
												 	 ),
										'he3' =>array(
													'joinEntity'=>'housing_estate' ,
												  	'onClause'=> array(
																		'leftEntity'=>'estate_id_choice3',
																		'rightEntity'=>'estate_id'
																		),
													'joinType'=> 'left'
												 	 ),
										'he4' =>array(
													'joinEntity'=>'housing_estate' ,
												  	'onClause'=> array(
																		'leftEntity'=>'estate_id_choice4',
																		'rightEntity'=>'estate_id'
																		),
													'joinType'=> 'left'
												  	), 
									    'hft' =>array(
													'joinEntity'=>'housing_flat_type' ,
												  	'onClause'=> array(
																		'leftEntity'=>'flat_type_id',
																		'rightEntity'=>'flat_type_id'
																		),
													'joinType'=> 'left'
												 	 ), 
									    
										),
						  'fields'=>array(
										 
										 
										  'hna'=>array('Allotment Reason' =>array('allotment_category','allotment_category')),
										  'hft'=>array('Flat Type'=>array('flat_type','flat_type')),
										  //'he1'=>array('1st Estate Choice'=>array('estate_name','estate1')),
										  //'he2'=>array('2nd Estate Choice'=>array('estate_name','estate2')),
										  //'he3'=>array('3rd Estate Choice'=>array('estate_name','estate3')),
										  //'he4'=>array('4th Estate Choice'=>array('estate_name','estate4')),
										  ),
				  		'expressions'=>array(),
						 'condition' => array()
						  );
