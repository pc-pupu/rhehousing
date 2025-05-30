<?php
function user_profile_form($form, &$form_state) {
    global $user;

    $user_info = getApplicantInfo();

    $query ='SELECT he.estate_name,he.estate_address, hft.flat_type
                FROM housing_online_application hoa
                INNER JOIN housing_applicant_official_detail haod ON haod.applicant_official_detail_id = hoa.applicant_official_detail_id
                INNER JOIN housing_flat_occupant hfo ON hfo.online_application_id = hoa.online_application_id
                INNER JOIN housing_flat hf ON hf.flat_id = hfo.flat_id
                INNER JOIN housing_estate he ON he.estate_id = hf.estate_id
                INNER JOIN housing_flat_type hft ON hft.flat_type_id = hf.flat_type_id
                WHERE haod.uid = '.$user->uid.''; 
    $result = db_query($query);

    if ($result->rowCount() > 0) {
        foreach ($result as $row) {
            $user_info[] = array(
                'estate_name' => $row->estate_name,
                'estate_address' => $row->estate_address,
                'flat_type' => $row->flat_type,
            );
        }
    } else {
        drupal_set_message('No allotment data found.', 'warning');
    }
    // print_r($user_info);die;

    // applicant pamanent address and official address

    $output = '<div class="col-md-6">Address</div>';

    $form['markupdata'] = array(
        '#type' => 'markup',
        '#markup' => $output
    );
    
    return $form;
    
}
    
