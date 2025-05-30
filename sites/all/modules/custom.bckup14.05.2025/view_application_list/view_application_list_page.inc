<?php

function view_app_page($status ='', $entity = '',$page_status ='') {
	
	// echo $entity;echo $status;echo $page_status ;die();
	global $user_role,$user;
	$status = decrypt_url($status);
	//echo $status;die;
	$entity = decrypt_url($entity);
	//  echo $status;die();
	// echo $entity; die; //echo $status;echo $page_status ;die();
	$output = '';
	$rows =array(); //sd turned off 21-06-2024 //debaleena turned on 09-07-2024
	//$header = array(); //sd turned off 21-06-2024
	$statusMsg ='';
	
	if($status !== '' && $entity !== '' && preg_match("/^[a-zA-Z0-9\-\_]*$/",$status) && preg_match("/^[a-zA-Z0-9\-\_]*$/",$entity)){
		if($status == 'applied'){
			$statusMsg = 'Submitted ';
		}else if($status == 'ddo_verified_1'){
			$statusMsg = 'DDO (Level-1) Verified ';
		}else if($status == 'ddo_rejected_1'){
			$statusMsg = 'DDO (Level-1) Rejected ';
		}else if($status == 'housing_sup_approved_1'){
			$statusMsg = 'Housing Supervisor(Level-1) Verified ';
		}else if($status == 'housing_sup_reject_1'){
			$statusMsg = 'Housing Supervisor(Level-1) Rejected ';
		}else if($status == 'housingapprover_approved_1'){    //debaleena 04-09-2024
			$statusMsg = 'Housing Approver Verified ';
		}else if($status == 'housingapprover_reject1'){
			$statusMsg = 'Housing Approver Rejected ';
		}else if($status == 'housing_official_approved'){
			$statusMsg = 'Housing Official Verified ';
		}else if($status == 'housing_official_rejected'){
			$statusMsg = 'Housing Official Rejected ';
		}else if($status == 'ddo_verified_2'){
			$statusMsg = 'DDO (Level-2) Verified ';
		}else if($status == 'ddo_rejected_2'){
			$statusMsg = 'DDO (Level-2) Rejected ';
		}else if($status == 'housing_sup_approved_2'){
			$statusMsg = 'Housing Supervisor(Level-2) Verified ';
		}else if($status == 'housing_sup_reject_2'){
			$statusMsg = 'Housing Supervisor(Level-2) Rejected ';
		}else if($status == 'applicant_acceptance'){
			$statusMsg = 'Allotted ';
		}else if($status == 'housingapprover_approved_2'){    //debaleena 12-09-2024
			$statusMsg = 'Housing Approver Verified ';
		}else if($status == 'housingapprover_reject2'){
			$statusMsg = 'Housing Approver Rejected ';
		}


		/*else if($status == 'verified'){
			$statusMsg = 'Verified ';
		}
		else if($status == 'reject'){
			$statusMsg = 'Rejected ';
		}*/
		
		if($entity == 'new-apply'){
			$entityMsg = 'New Allotment ';
		}
		else if($entity == 'vs'){
			$entityMsg = 'Vertical Shifting ';
		}
		else if($entity == 'cs'){
			$entityMsg = 'Category Shifting ';
		}
		else if($entity == 'new_license'){
			$entityMsg = 'New Licence ';
		}
		
		//new code
		else if($entity == 'vs_licence'){
			$entityMsg = 'VS Licence ';
		}
		else if($entity == 'cs_licence'){
			$entityMsg = 'CS Licence ';
		}
		//
		
		else if($entity == 'renew_license'){
			$entityMsg = 'Renew Licence ';
		}
		// echo $statusMsg;die;	
		drupal_set_title($statusMsg.'Application List for '.$entityMsg);
			
		
		// $result = fetch_all_application_detail1($entity,$status);
		if($page_status=='action-list'){
			// echo $status;die;
			$result = application_list_fetch($entity,$status);//sd
		}else if($page_status=='verified-list'|| $page_status=='reject-list'){
			// echo $status;die;
			$result = application_list_fetch_for_verified_reject($entity,$status);
		}
		
		// if($user->name == 'osd_housing'){   //debaleena 09-08-2024
		// 	$online_application_status = fetch_online_application_status($user->uid);
		// 	$online_application_status= $online_application_status->short_code ;
		// }
			


		$header = array(
			'applicant_name' => array(
				'data' => 'Name'
			) ,
			'application_no' => array(
				'data' => 'Application No.',
				'width'=>'20%'
			) 
		);
		
		
		// if($status == 'applied' || $status == 'ddo_verified_1' || $status == 'housing_sup_approved_1' || $status == 'housing_official_approved'){
		// 	$header['date_of_application'] = array('data' => 'Date of Application');
		// }
		//$header[] = array('data' => 'Time of Application');
		
		if($entity == 'new-apply'||$entity == 'vs'||$entity == 'cs'){//echo $status;
			if($page_status == 'verified-list'|| $page_status=='reject-list'){
				
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['approval_or_rejection_date'] = array('data' => 'Approval/Rejection Date');
				$header['Status'] = array('data' => 'Status');
				$header['view'] = array('data' => 'View');

				// if($user->name == 'osd_housing'){   //debaleena 09-08-2024
				// // echo $status;die;
				// 	if($page_status == 'verified-list' && $online_application_status == 'housing_sup_approved_2' && $status == 'housing_sup_approved_2'){
				// 		$header['generate_license'] = array('data' => 'License Generation', 'width'=>'20%');
				// 	}
				// 	// echo $status;die();
				// 	if($page_status == 'verified-list' && $online_application_status == 'license_generate' && $status == 'housing_sup_approved_2'){
						
				// 		$header['Download Licence'] = array('data' => 'Download Licence', 'width'=>'20%');
				// 	}
				// }
				
				

			}else{
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
				$header['action'] = array('data' => 'Action', 'width'=>'10%');
				//$header['reject_remarks'] = array('data' => 'Remarks', 'width'=>'15%');
			}
			/*if($status=='applied'||$status=='ddo_verified_1'||$status=='housing_sup_approved_1'||$status=='alloted'||$status=='applicant_acceptance'||$status=='ddo_verified_2'){
				// echo"i am here";echo $status;
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
				$header['action'] = array('data' => 'Action', 'width'=>'20%');
			}else{
				// echo"i am in else";
				$header['date_of_application'] = array('data' => 'Date of Application');
				$header['flat_type'] = array('data' => 'Flat Type');
				$header['allotment_category'] = array('data' => 'Allotment Reason');
				$header['computer_serial_no'] = array('data' => 'Computer Serial No');
				$header['view'] = array('data' => 'View');
			}
			*/
			
		}
		else if($status == 'reject'){
			$header[] = array('data' => 'Reject Date');
		}
		//$header[] = array('data' => 'View');
		
	
		 while($data = $result->fetchObject()) {

			//$onclick2 = "return confirm('Are you sure you want to generate License for ?')";
			$msg = 'Are you sure you want to generate License for Application No.=' .$data->application_no.'?';
			//echo $aa;die;
			$onclick2 = "return confirm('$msg' )";
			// print_r($data);die;
			$fields = array();
			if($entity == 'new-apply' || $entity == 'vs'||$entity == 'cs' ){
				

				if($page_status == 'verified-list'|| $page_status == 'reject-list'){

					$fields[] = $data->applicant_name;
					$fields[] = $data->application_no;
					$fields[] = implode('/', array_reverse(explode('-', $data->date_of_application)));
					$fields[] = $data->flat_type;
					$fields[] = ($data->allotment_category=='')?'Not Applicable':$data->allotment_category;
					$fields[] = ($data->computer_serial_no=='')?'Not Applicable':$data->computer_serial_no;
					$fields[] = $data->created_at;
					$fields[] = $data->status_description;
					global $base_path;
			 		$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
					$fields[] = l(
									'View',
									'application_detail/'.encrypt_url($data->online_application_id).'/'.'verified-list'.'/'.encrypt_url($status), //
									array(
											'html'=>TRUE,
											'attributes'=> array('target' => '_blank','class'=>array('btn bg-primary btn-sm px-4 rounded-pill text-white fw-bolder')),
									)
								);
					// if($user->name == 'osd_housing'){
					// 	echo $online_application_status;die;   //debaleena 09-08-2024			
					// 	if($page_status == 'verified-list' && $online_application_status == 'housing_sup_approved_2' && $status =='housing_sup_approved_2'){
					// 		$fields[] = l(
					// 			'<span class="text-danger" style="font-size:20px"></span><span class="btn bg-success btn-sm text-white rounded" style="font-size:12px" > Generate License</span>' ,
					// 			'generate-license/'.encrypt_url($data->online_application_id).'/'.'verified-list'.'/'.encrypt_url($status),
					// 				array('html'=>TRUE, 'attributes' => array('onclick' => $onclick2))
					// 			);	
					// 	}
						
					// 	if($page_status == 'verified-list' && $online_application_status == 'license_generate' && $status == 'housing_sup_approved_2'){
							
					// 		$fields[] = l(
					// 			'<span class="btn bg-dark btn-sm fa fa-download text-white rounded" style="font-size:12px" ></span>' ,
					// 			'download_licence_pdf/'.encrypt_url($data->online_application_id).'/', //
					// 			array('html'=>TRUE,'attributes'=> array('target' => '_blank'))
					// 		); // Done by Subham 07-08-2024
					// 	}
					// }


				}else{

					$fields[] = $data->applicant_name;
					$fields[] = $data->application_no;
					$fields[] = implode('/', array_reverse(explode('-', $data->date_of_application)));
					$fields[] = $data->flat_type;
					$fields[] = ($data->allotment_category=='')?'Not Applicable':$data->allotment_category;
					$fields[] = ($data->computer_serial_no=='')?'Not Applicable':$data->computer_serial_no;
					global $base_path;
			 		$src=$base_path.drupal_get_path('module', 'view_application_list').'/images/view1.png';
					$fields[] = l(
								'View',
								'application_detail/'.encrypt_url($data->online_application_id).'/'.'action-list'.'/'.encrypt_url($status), 
								array(
											'html'=>TRUE,
											'attributes'=> array('target' => '_blank','class'=>array('btn bg-primary btn-sm px-5 rounded-pill text-white fw-bolder')),
									)
								);

					if($status == 'applied') {
						$update_status = 'ddo_verified_1';
						$reject_status = 'ddo_rejected_1';
					}else if($status == 'ddo_verified_1'){
						$update_status = 'housing_sup_approved_1';
						$reject_status = 'housing_sup_reject_1';
					}else if($status == 'housing_sup_approved_1'){
						$update_status = 'housingapprover_approved_1';     //debaleena 04-09-2024
						$reject_status='housingapprover_reject1';
					}else if($status == 'allotted'){
						$update_status = 'housing_official_approved';
						$reject_status='housing_official_reject';
					}else if($status == 'applicant_acceptance'){
						$update_status = 'ddo_verified_2';
						$reject_status='ddo_rejected_2';
					}else if($status == 'ddo_verified_2'){
						$update_status = 'housing_sup_approved_2';
						$reject_status='housing_sup_reject_2';
					}else if($status == 'housing_sup_approved_2'){
						$update_status = 'housingapprover_approved_2';     //debaleena 12-09-2024
						$reject_status='housingapprover_reject2';
					}


					
					

				

					$onclick="return confirm('Are you sure you want to approve?')";
					$onclick1="return confirm('Are you sure you want to reject?')";
					if($reject_status == 'housing_sup_reject_1' || $reject_status == 'housing_official_reject' || $reject_status == 'housing_sup_reject_2' || $reject_status == 'housingapprover_reject2' || $reject_status == 'housingapprover_reject1')
					{
						// echo "kkk";die;
						$fields[] = l('<span class="badge text-bg-success rounded fa fa-check">
						</span>' ,'application-approve/'.encrypt_url($data->online_application_id).'/'.encrypt_url($update_status).'/'.encrypt_url($status).'/'.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick))).'&nbsp;'.
						l('<span class="badge text-bg-danger rounded fa fa-times" > </span>' ,'application_detail/'.encrypt_url($data->online_application_id).'/'.'action-list'.'/'.
						encrypt_url($reject_status),array('html'=>TRUE));

					}else{
						//echo "hhh";die;

						// $fields[] = l('<span class="badge text-bg-success rounded fa fa-check">
						// </span>' ,

						// 'c/'.encrypt_url($data->online_application_id).'/'.encrypt_url($update_status).'/'.encrypt_url($status).'/
						// '.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick))).' '.

						// l(
						// 	'<span class="badge text-bg-danger rounded fa fa-times" > </span>' ,
						// 'update_status/'.encrypt_url($data->online_application_id).'/'.encrypt_url($reject_status).'/'.encrypt_url($status).'/'.encrypt_url($entity),
						// 	array('html'=>TRUE, 'attributes' => array('onclick' => $onclick1))
						// );



						$fields[] = l('<span class="badge text-bg-success rounded fa fa-check">
						</span>','application-approve/'.encrypt_url($data->online_application_id).'/'.encrypt_url($update_status).'/'.encrypt_url($status).'/'.encrypt_url($entity), array('html'=>TRUE, 'attributes' => array('onclick' => $onclick))).'&nbsp;'.
						l('<span class="badge text-bg-danger rounded fa fa-times" > </span>','update_status/'.encrypt_url($data->online_application_id).'/'.encrypt_url($reject_status).'/'.encrypt_url($status).'/'.encrypt_url($entity),array('html'=>TRUE, 'attributes' => array('onclick' => $onclick1)));

					}	




				}
			}
				
			// 'update_status/'.encrypt_url($data->online_application_id).'/'.encrypt_url($reject_status).'/'.encrypt_url($status).'/'.encrypt_url($entity),

			$rows[] = $fields;
			  // if()
			  // echo "<pre>";print_r($rows[0][6]);die;
		 }
		
		/*$output = theme_table(
			array(
			  'header' => $header,
			  'rows' => $rows,
			  'attributes' => array(),
			  'sticky' => true,
			  'caption' => '',
			  'colgroups' => array(),
			  'empty' => t("No data found!") // The message to be displayed if table is empty
			)
	  	).theme('pager');*/

		
		// sd 21-06-2024 start
		$variables = array(
			'attributes' => array('class'=>array('table table-list table-striped')),
			'header' => $header,
			'rows' => $rows,
			'sticky' => true,
			'empty' => t("No data found!") // The message to be displayed if table is empty
		  );
  		//end
		//sd turned off 21-06-2024
		if(count($rows) > 0) {
			// Render using Drupal's render API.
			$build['datatable'] = array(
			  '#theme' => 'datatable',
			  '#header' => $header,
			  '#rows' => $rows,
			  '#attributes' => array(),
			);
			
			// Or, render using a theme function.
			$variables = array(
			  'attributes' => array('class'=>array('table table-list table-striped')),
			  'header' => $header,
			  'rows' => $rows,
			);
			
			$output = theme('datatable', $variables);
		}
		else {
			$output = '<div>
							<table class="datatable_no_data_found table table-list">
								<tr class="tr_no_data_found">
									<th class="th_no_data_found"></th>
								</tr>
								<tr class="tr_no_data_found">
									<td class="td_no_data_found">No data found!</td>
								</tr>
							</table>
						</div>';
		}
	}
	return $output;
}






//end
