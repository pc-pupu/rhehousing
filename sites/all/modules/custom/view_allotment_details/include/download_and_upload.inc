<?php

function download_and_upload($form, &$form_state, $online_application_id = ''){
    global $base_path;

    // echo decrypt_url($online_application_id); die;
   // if($housing_online_status == 'applicant_acceptance_incomplete'){

         // Add a new item to the bottom of the form.
     $form['my_custom_note'] = array(
        '#type' => 'markup',
        '#markup' => '<br><div class="row" style="padding-right:20px;"><p style="color: red;">**Note : Please download the Application Form and Declaration Form.You have to 
        sign these documents and upload duly signed License Application Form,Declaration and Latest Payslip. </p></div>',
        
        
      );

    $form['markup_application'] = array(
        '#type' => 'markup',
        '#markup' => '<br><div class="row"><div class="col-md-6">'.l('<img height="20" width="20" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png" title="Download Application Form" alt="PDF Icon"> Download License Application Form ', 'form-of-application/'.$online_application_id, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div>'
    ); 

    $form['markup_declaration'] = array(
        '#type' => 'markup',
        '#markup' => '<div class="col-md-6">'.l('<img height="20" width="20" src="'.$base_path.drupal_get_path('module', 'application_of_registration_list').'/images/download_icon.png" title="Download Declaration" alt="PDF Icon"> Download Declaration ', 'generate-declaration/'.$online_application_id, array('html'=>TRUE, 'attributes' => array('target' => '_blank', 'style' => 'color: #0090C7;font-weight: 400;text-decoration: none; font-size:14px'))).'</div></div>'

        
    );

    $form['licence_application_file'] = array(
        '#title' => t('Upload Licence Application Signed Form'),
        '#type' => 'managed_file',
        '#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>') ,
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#default_value' => variable_get('Upload File', ''),
        '#upload_validators' => array(
                                        'file_validate_extensions' => array("pdf"),
                                        // 'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
                                        'file_validated_size' => array(2*1024*1024),
                                     ),
        '#upload_location' => 'public://doc/tmp/',
        '#required' => TRUE,
        '#process' => array('download_and_upload_element_process'),
    );
    
    $form['declaration_file'] = array(
        '#title' => t('Upload Declaration Signed Form'),
        '#type' => 'managed_file',
        '#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>') ,
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#default_value' => variable_get('Upload File', ''),
        '#upload_validators' => array(
                                        'file_validate_extensions' => array("pdf"),
                                        // 'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
                                        'file_validated_size' => array(2*1024*1024),
                                     ),
        '#upload_location' => 'public://doc/tmp/',
        '#required' => TRUE,
        '#process' => array('download_and_upload_element_process'),
    );

    $form['payslip_file'] = array(
        '#title' => t('Upload Current Pay Slip'),
        '#type' => 'managed_file',
        '#description' => t('<b>Allowed Extension: pdf<br>Maximum File Size: 2 MB</b>') ,
        '#progress_message' => t('Please wait...'),
        '#progress_indicator' => 'bar',
        '#default_value' => variable_get('Upload File', ''),
        '#upload_validators' => array(
                                        'file_validate_extensions' => array("pdf"),
                                        // 'file_validated_size' => array(MAX_FILE_SIZE*1024*1024),
                                        'file_validated_size' => array(2*1024*1024),
                                     ),
        '#upload_location' => 'public://doc/tmp/',
        '#required' => TRUE,
        '#process' => array('download_and_upload_element_process'),
    );

    $form['online_application_id'] = array(
        '#type' => 'hidden',
        '#value' => $online_application_id
    );


    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Upload Signed Documents'),
        '#attributes'=>array('class'=>array('text-centre btn bg-primary btn-sm px-5 mt-5 rounded-pill text-white fw-bolder')),
        
    );


    
    
    return $form;


   // }
        
}

function download_and_upload_element_process($element, &$form_state, $form) {
    $element = file_managed_file_process($element, $form_state, $form);
    $element['upload_button']['#access'] = FALSE;
    return $element;
}


function download_and_upload_submit($form, &$form_state) {
    global $user;

    $online_application_id = $form_state['values']['online_application_id'];
    // echo $online_application_id;die;
    $docArr = array();

    if (!empty($form_state['values']['licence_application_file'])) {
        // Load the file object.
        $file = file_load($form_state['values']['licence_application_file']);
        $dynamic_folder = 'public://doc/'. $user->uid;
        file_prepare_directory($dynamic_folder, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
        $file_name = time().$file->filename;
        $destination = $dynamic_folder . '/' .$file_name ;
        $file = file_copy($file, $destination, FILE_EXISTS_REPLACE);
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        $fid = $file->fid;
        $docArr['licence_file']['fid'] = $fid;
        $docArr['licence_file']['filename'] = $file_name;
        $docArr['licence_file']['filetype'] = 'license_application_signed_form';
    }

    if (!empty($form_state['values']['declaration_file'])) {
        // Load the file object.
        $file = file_load($form_state['values']['declaration_file']);
        $dynamic_folder = 'public://doc/'. $user->uid;
        file_prepare_directory($dynamic_folder, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
        $file_name = time().$file->filename;
        $destination = $dynamic_folder . '/' .$file_name ;
        $file = file_copy($file, $destination, FILE_EXISTS_REPLACE);
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        $fid = $file->fid;
        $docArr['declaration_file']['fid'] = $fid;
        $docArr['declaration_file']['filename'] = $file_name;
        $docArr['declaration_file']['filetype'] = 'declaration_signed_form';
    }
    if (!empty($form_state['values']['payslip_file'])) {
        // Load the file object.
        $file = file_load($form_state['values']['payslip_file']);
        $dynamic_folder = 'public://doc/'. $user->uid;
        file_prepare_directory($dynamic_folder, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
        $file_name = time().$file->filename;
        $destination = $dynamic_folder . '/' .$file_name ;
        $file = file_copy($file, $destination, FILE_EXISTS_REPLACE);
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        $fid = $file->fid;
        $docArr['payslip_file']['fid'] = $fid;
        $docArr['payslip_file']['filename'] = $file_name;
        $docArr['payslip_file']['filetype'] = 'current_pay_slip';
    }

    if(!empty($docArr)){
        foreach($docArr as $r){ 
            $arrins = array(
                'online_application_id' => decrypt_url($online_application_id),
                'uid' => $user->uid,
                'verified_date' => date('Y-m-d H:i:s'),
                'is_active' => 1,
                'doc_fid' => $r['fid'],
                'doc_filename' => $r['filename'],
                'doc_type' => $r['filetype']
            );
            
            db_insert('housing_online_application_upload_doc')->fields($arrins)->execute();
        }

    }

    /////code added by debaleena 25-11-2024////
        db_update('housing_flat_occupant')
			->fields(array('accept_reject_status' => 'Accept'))  
			->condition('online_application_id', decrypt_url($online_application_id), '=')
			->execute();

		db_update('housing_online_application')
			->fields(array('status' => 'applicant_acceptance'))  
			->condition('online_application_id', decrypt_url($online_application_id), '=')
			->execute();
        $status_id = get_status_id('applicant_acceptance');
		$ins_arr = array(
				'online_application_id'=> decrypt_url($online_application_id),
				'status_id' => $status_id,
				'created_at' => date('Y-m-d H:i:s'),
				'uid' => $user->uid,
				'short_code' => 'applicant_acceptance'   
			);

		db_insert('housing_process_flow')->fields($ins_arr)->execute();
    /////////end////////////

    drupal_set_message(t('The documents has been uploaded successfully.'));
    drupal_goto('dashboard');
}


