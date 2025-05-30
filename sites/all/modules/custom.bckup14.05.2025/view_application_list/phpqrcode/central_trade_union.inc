<?php

function central_trade_union_list(){			
	$ctu_list = db_select('l_ctu_master', 'lctm');
	$ctu_list->fields('lctm', array('name', 'registration_no', 'affiliation_number', 'registration_date','is_active','id'));
	$ctu_list = $ctu_list->execute(); 
	
	$header = array(
			  array('data' => 'Sl', 'width' => '5%'),
			  array('data' => 'Central Trade Union/ Federation Name', 'width' => '30%'),
			  array('data' => 'Status', 'width' => '10%'),
			  array('data' => 'Operation', 'width' => '10%'),
		  );
		 
	if( $ctu_list->rowCount() > 0 ){
		$counter = 0;  
		$view_img = '<span class="badge bg-blue"><i class="fa fa-eye"></i> View Details';
			
		foreach($ctu_list as $data){
			$counter++;
			if($data->is_active=='N'){
				$status='<font color="#FF0000">Inactive</font>';
			}else{
				$status='<font color="#00CC00">Active</font>';
			}
			if(!empty($data->registration_date)){
				$reg_date=date('d-m-Y', strtotime($data->registration_date));
			}else{
				$reg_date='NIL';
			}
			$view_link = l('<i class="fa fa-eye"></i> View', 'central-trade-union-list-view/'.encryption_decryption_fun('encrypt', $data->id), array('html' => TRUE));
			
			$rows[] = array(
						array('data' => $counter, 'align' => 'left'),
						array('data' => '<strong>'.$data->name.'</strong>', 'align' => 'left'),
						array('data' => $status, 'align' => 'left'),
						array('data' => l($view_link, '#', array('html' => TRUE, 'attributes' => array('target' => '_blank'))), 'align' => 'left'),
					);
			}
	}
	
	$variables = array(
			'attributes' => array('class' => array('table table-striped table-responsive admin-custom-table')), 
			'header' => $header,
			'rows' => $rows,
			'empty' => t("Data not available")
	  		);
	
	$output = theme('datatable', $variables);		
	return '<div class="row"><div class="col-md-12" id="fa-icons"><div class="box box-primary"><div class="box-body"><div class="feedback-scroll">'.$output.'</div></div></div></div></div>';	
}

function central_trade_union_list_view($form, &$form_state, $id = ''){
	drupal_add_css(drupal_get_path('module', 'trade_union') . '/css/trade_union.css');
	$pk_id = encryption_decryption_fun('decrypt', $id);
	
	$form['markup_data'] = array(
									'#markup' => view_ctu_application($pk_id),
									'#type' => 'markup',
									'#suffix' =>'</div>'
									);
												
	$form['action_markup'] = array(
									'#prefix' => '<div class="row"><div class="content"><div class="panel panel-default panel-form"><div class="panel-heading">&nbsp;Actions</h3></div><div class="box-body">',
									);
									
	$form['update'] = array(
						'#prefix' => '<div class="col-lg-6 col-md-6"><label class="input">',
						'#suffix' => '</label></div>',
						'#title' => 'Are you want to active this Central Trade Union',
						'#type' => 'select',
						'#options' => array('Y' => 'YES', 'N' => 'NO'),
						'#attributes' => array('class' => array('form-control pull-left')),							
						'#required' => TRUE,
						);
						
	$form['id'] = array(
						
						'#type' => 'hidden',
						'#default_value' => $pk_id
						);
						
	
						
	$form['save'] = array(	'#prefix' => '<div class="col-lg-12 col-md-12">',
							'#suffix' => '</div></div>',
							'#type'=> 'submit',
							'#value'=> 'Save',
							'#attributes'=> array('class' => array('btn btn-primary'), ),
							);
														
	
	$form['action_markup_end'] = array(
										'#prefix' => '<div class="col-md-12">&nbsp;</div></div></div></div>',
										);		
														
														
	
												
	return $form;
	
}

function view_ctu_application($id){

	$c_trade_Union	=	db_query('select * from l_ctu_master where id=:id', array( ':id' => $id ));	
	$c_trade_Union_final=	$c_trade_Union->fetchAssoc();	
	
	if($c_trade_Union_final['is_active']=='N'){
				$status='<font color="#FF0000">Inactive</font>';
			}else{
				$status='<font color="#00CC00">Active</font>';
			}
			
	$filepathSave 	= 'sites/default/files/upload/common/';
	if(!empty($c_trade_Union_final['notification'])){
		$notification = $c_trade_Union_final['notification'];
		
		if(!empty($notification)){
			
			$pdf_decoded1 = base64_decode($notification);
			$new_file_name='notification'.'_'.$c_trade_Union_final->id.'.pdf';
			drupal_unlink('sites/default/files/upload/common/'.$new_file_name);
			file_put_contents('sites/default/files/upload/common/'.$new_file_name, $pdf_decoded1);
		}else{
			$pdf_decoded1 = '';
		}
		
		$notification_pdf = $GLOBALS['base_url'].'/sites/default/files/upload/common/'.$new_file_name;
		$notificationDoc  = l('<img src="'.$GLOBALS['base_url']."/".drupal_get_path('theme', 'jackson').'/images/lc-pdf.png">',$notification_pdf,array('html' => TRUE, 'attributes' => array('target' => '_blank')));
	
	}
			
	$output='<div class="box box-solid">
    										  <div class="box-body" style="padding:0;">
												  <table border="0" class="table table-striped table-responsive admin-custom-table">
											
											<tr>
												<th width="30%">Parameters</th>
												<th>Inputs'.l('<i class="fa fa-print fa-1x"></i>', 'trade-union-master-list/print/'.$pre_id.'/TRADE-UNION-'.$e_trade_union_regn_no, array('attributes' => array('class' => array('pull-right'), 'target' => '_blank'), 'html' => TRUE)).'</th>
											</tr>
											'.$disable_msg.'
											
											<tr>
												<td>Name</td>
												<td>'.$c_trade_Union_final['name'].'</td>
											</tr>
											<tr>
												<td>Address</td>
												<td>'.$c_trade_Union_final['ctu_address'].'</td>
											</tr>
											<tr>
												<td>Phone No</td>
												<td>'.$c_trade_Union_final['ctu_phone'].'</td>
											</tr>
											<tr>
												<td>Email</td>
												<td>'.$c_trade_Union_final['ctu_office_email'].'</td>
											</tr>
											<tr>
												<td>Notification File</td>
												<td>'.$notificationDoc.'</td>
											</tr>																					
											<tr>
												<td>Status</td>
												<td>'.$status .'</td>
											</tr>
																											
										</table>
									 </div>';
				

	return $output;
	
	
}

function central_trade_union_list_view_submit($form, $form_state){
	
	global $user; 
	$id=$form_state['values']['id'];
	$fields = array(
					'is_active'=> trim($form_state['values']['update']),
					
					);
					
	db_update('l_ctu_master')->fields($fields)->condition('id',$id)->execute();
					
	drupal_goto('central-trade-union-list/');
					
	
}
?>