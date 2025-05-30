<?php

function status_update_page($online_application_id = '', $status = '') {
	
	global $user;
	$online_id = decrypt_url($online_application_id);
	$accept_reject_status = decrypt_url($status);
	
	$result = fetch_allotment_details();
	$data = $result->fetchObject();

	$transaction = db_transaction();

	try{		
		
		if($accept_reject_status == 'Accept') {	
			
			//turned off code by debaleena 26-11-2024 for no work on click accept button/////
			// db_update('housing_flat_occupant')
			// ->fields(array('accept_reject_status' => 'Accept_Incomplete'))  // Acept to Accept_Incomplete changed by debaleena 25-11-2024
			// ->condition('online_application_id', $online_id, '=')
			// ->execute();

			// db_update('housing_online_application')
			// ->fields(array('status' => 'applicant_acceptance_incomplete'))  // applicant_acceptance to  applicant_acceptance_incomplete changed by debaleena 25-11-2024
			// ->condition('online_application_id', $online_id, '=')
			// ->execute();

			// $ins_arr = array(
			// 	'online_application_id'=>$online_id,
			// 	'status_id' => 25,
			// 	'created_at' => date('Y-m-d H:i:s'),
			// 	'uid' => $user->uid,
			// 	'short_code' => 'applicant_acceptance_incomplete'   // applicant_acceptance to  applicant_acceptance_incomplete changed by debaleena 25-11-2024
			// );

			// db_insert('housing_process_flow')->fields($ins_arr)->execute();

			/////end////
			drupal_set_message('You accepted the allotment.');
			// drupal_goto('view_allotment_details');
			drupal_goto('download-and-upload/'.$online_application_id);
			
		}
		else if($accept_reject_status == 'Reject'){
			// echo $online_id;die;
			/*$reject_offer_arr = array();
			$reject_offer_arr['status']  = 'reject_offer';
			$reject_offer_arr['online_application_id']  = $online_id;
		
			db_update('housing_online_application')
			->fields($reject_offer_arr)
			->condition('online_application_id', $reject_offer_arr['online_application_id'])
			->execute();*/

			db_update('housing_online_application')
			->fields(array('status' => 'applicant_reject'))
			->condition('online_application_id', $online_id, '=')
			->execute();

			$status_id = get_status_id('applicant_reject');
			

			$ins_arr = array(
				'online_application_id'=>$online_id,
				'status_id' => $status_id,
				'created_at' => date('Y-m-d H:i:s'),
				'uid' => $user->uid,
				'short_code' => 'applicant_reject'
			);

			db_insert('housing_process_flow')->fields($ins_arr)->execute();

			////addded by dg 13-12-2024///
			$query = db_select('housing_applicant_official_detail','haod');
			$query->innerjoin('housing_online_application ', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
			$query->leftjoin('housing_flat_occupant ', 'hfo', 'hfo.online_application_id = hoa.online_application_id');
			$query->addField('haod', 'applicant_official_detail_id');
			$query->addField('hfo', 'flat_id');
			$query->condition('hoa.online_application_id', $online_id, '=');
			$result = $query->execute();
			$data = $result->fetchObject();
			// print_r($data);die;

			db_update('housing_applicant_official_detail')
			->fields(array(
				'is_active' => 0,
				)
			)
			->condition('applicant_official_detail_id',$data->applicant_official_detail_id, '=')
			->execute();

			if(isset($data->flat_id)){
				db_update('housing_flat')
					->fields(array(
						'flat_status_id' => 1,
						)
					)
			->condition('flat_id',$data->flat_id, '=')
			->execute();
			}
			///end///
	
			
			// db_update('housing_flat')
			// ->fields(array('flat_status_id' => 1))
			// ->condition('flat_id', $data->flat_id, '=')
			// ->execute();
			
			db_update('housing_flat_occupant')
			->fields(array('accept_reject_status' => 'Reject'))
			->condition('online_application_id', $online_id, '=')
			->execute();
			
			//db_query('update housing_flat set flat_status_id = 1 where flat_id = '.$data->flat_id);	
			drupal_set_message('You reject the allotment.');
			drupal_goto('view_allotment_details');
		}
	}catch(Exception $e){
		$transaction->rollback();
    	watchdog_exception('my_type', $e);
		throw $e;
	}
}