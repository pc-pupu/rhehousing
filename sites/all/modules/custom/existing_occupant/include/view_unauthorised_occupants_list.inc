<?php // Done by Subham dt. 07-01-2025 & 08-01-2025
function view_unauthorised_occupants_list(){
    $current_date = date('Y-m-d');
    $query = db_select('housing_online_application', 'hoa');
    $query->innerJoin('housing_applicant_official_detail', 'haod', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
    $query->innerJoin('housing_applicant', 'ha','ha.housing_applicant_id = haod.housing_applicant_id');
    $query->innerJoin('housing_flat_occupant', 'hfo','hoa.online_application_id = hfo.online_application_id');
    $query->leftJoin('housing_occupant_license', 'hol', 'hol.flat_occupant_id = hfo.flat_occupant_id');
    $query->addField('ha', 'applicant_name');
    $query->addField('hoa', 'application_no');
    $query->fields('hol', array('license_no', 'possession_date', 'license_expiry_date', 'flat_occupant_id', 'authorised_or_not'));
    $query->condition('hol.license_expiry_date', $current_date, '<');
    $or = db_or()
          ->isNull('hol.authorised_or_not')
          ->condition('hol.authorised_or_not', 'unauthorised');

    $query->condition($or);
    //$query->condition('hol.authorised_or_not', NULL, 'IS');
    $result = $query->execute();
    
    
    $header['Sl No.'] = array('data' => 'Sl No.');
    $header['Applicant Name'] = array('data' => 'Applicant Name');
    $header['Application No.'] = array('data' => 'Application No.');
    $header['License No.'] = array('data' => 'License No.');
    $header['Possession Date'] = array('data' => 'Possession Date');
    $header['License Expiry Date'] = array('data' => 'License Expiry Date');
    $header['Action'] = array('data' => 'Action');

    $rows = array();
    $output = '';
    $serialNumber = 1;
   
    while ($data = $result->fetchObject()) {
        $fields = array();

        $fields[] = $serialNumber;
        $fields[] = $data->applicant_name;
        $fields[] = $data->application_no;
        $fields[] = $data->license_no;
        $fields[] = $data->possession_date ? date('d-m-Y', strtotime($data->possession_date)) : '';
        $fields[] = $data->license_expiry_date ? date('d-m-Y', strtotime($data->license_expiry_date)) : '';
        $onclick = "return confirm('Are you sure you want to mark this applicant as Unauthorised?')";

        if($data->authorised_or_not == ''){
           $fields[] = l('<span class="btn bg-info btn-sm text-black rounded" style="font-size:12px"><b>Mark as Unauthorised</b></span>',
            'view-unauthorised-occupants-store/' . encrypt_url($data->flat_occupant_id), array('html' => TRUE,'attributes' => array('onclick' => $onclick))
            ); 
        }else if($data->authorised_or_not == 'unauthorised'){
            $fields[] = 'Marked as '.$data->authorised_or_not;
        }
        
        
        $serialNumber++;
        $rows[] = $fields;
    }

    $variables = array(
        'attributes' => array('class'=>array('table table-list table-striped')),
        'header' => $header,
        'rows' => $rows,
        'sticky' => true,
        'empty' => t("No data found!")
        );

    if(count($rows) > 0) {
        $build['datatable'] = array(
            '#theme' => 'datatable',
            '#header' => $header,
            '#rows' => $rows,
            '#attributes' => array(),
        );

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

    return $output;
}

/* Done by Subham 08-01-2025 */
function unauthorised_occupants_list_store($flat_occupant_id) {
    $dc_flat_occupant_id = decrypt_url($flat_occupant_id);

    db_update('housing_occupant_license')
        ->fields(array(
            'authorised_or_not' => 'unauthorised',
        ))
        ->condition('flat_occupant_id', $dc_flat_occupant_id, '=')
        ->execute();

    drupal_set_message(t('Successfully marked as Unauthorised!'));
    drupal_goto('view-unauthorised-occupants');
}
