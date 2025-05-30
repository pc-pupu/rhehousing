<?php // Done by Subham 19-12-2024
function transferred_ddo_list_form($form, &$form_state) {
    $form['date_dropdown'] = array(
        '#type' => 'select',
        '#title' => t('Date'),
        '#options' => fetch_ddo_transfer_date(),
        '#required' => TRUE,
        '#ajax' => array(
            'event' => 'change',
            'callback' => '_reload_ddo',
            'method' => 'replace',
        ),
        '#attributes' => array('class' => array('form-select')),
        '#prefix' => '<div class="row"><div class="col-md-3 form-floating">',
        '#suffix' => '</div></div>',
        '#default_value' => '', //17-12-2024
    );

    $form['transferred_ddo_list'] = array(
        '#type' => 'markup',
        '#markup'=> '<div id="transferred_employee_info_id"></div>'
    );

    if (isset($form_state['values']['date_dropdown']) && $form_state['values']['date_dropdown'] != '') {
        $date_dropdown = $form_state['values']['date_dropdown']; 
    } else {
        $date_dropdown = '';
    }    

    if($date_dropdown != '' ) { 
        $form['transferred_ddo_list'] = array(
            '#type' => 'markup',
            '#markup' => '<div class="col-md-12" id="transferred_employee_info_id">'.view_transferred_ddo_list($date_dropdown).'</div>',
        );
    }

    return $form;
}

function _reload_ddo($form, &$form_state) {
    $commands = array();
    $commands[] = ajax_command_replace("#transferred_employee_info_id", drupal_render($form['transferred_ddo_list']));
    return array('#type' => 'ajax', '#commands' => $commands);
}

// 17-12-2024
function view_transferred_ddo_list($date_dropdown) {
    // echo $date_dropdown; die;
    $header[] = array('data' => 'SL No.');
    $header[] = array('data' => 'Application Number');
    $header[] = array('data' => 'Applicant Name');
    $header[] = array('data' => 'Applicant Designation');
    $header[] = array('data' => 'DDO Code (NEW)');
    $header[] = array('data' => 'DDO Code (OLD)');
    $header[] = array('data' => 'Flat Details');
    $output='';
    $query = db_select('housing_applicant_ddo_transfer', 'hadt');
    $query->fields('hadt', array('ddo_code_new', 'ddo_code_old', 'online_application_id'));
    $query->innerJoin('housing_online_application', 'hoa', 'hadt.online_application_id = hoa.online_application_id');
    $query->innerJoin('housing_applicant_official_detail', 'haod', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
    $query->innerJoin('housing_applicant', 'ha', 'ha.housing_applicant_id = haod.housing_applicant_id');
    $query->innerJoin('housing_flat_occupant', 'hfo', 'hfo.online_application_id = hoa.online_application_id');
    $query->innerJoin('housing_flat', 'hf', 'hf.flat_id = hfo.flat_id');
    $query->innerJoin('housing_estate', 'he', 'hf.estate_id = he.estate_id');
    $query->innerJoin('housing_flat_type', 'hft', 'hf.flat_type_id = hft.flat_type_id');
    $query->innerJoin('housing_district', 'hd', 'he.district_code = hd.district_code');
    $query->addField('haod', 'applicant_designation');
    $query->addField('ha', 'applicant_name');
    $query->addField('hoa', 'application_no');
    $query->addField('hf', 'flat_no');
    $query->addField('hft', 'flat_type');
    $query->addField('he', 'estate_name');
    $query->addField('he', 'estate_address');
    $query->addField('hd', 'district_name');
    $query->condition('hadt.created_datetime', $date_dropdown, '=');
    $result=$query->execute();
    $i = 1;
    while($data = $result->fetchObject()) {
        $fields = array();
        $fields[] = $i;
        $fields[] = $data->application_no;
        $fields[] = $data->applicant_name;
        $fields[] = $data->applicant_designation;
        $fields[] = $data->ddo_code_new;
        $fields[] = $data->ddo_code_old;
        $flat_data_string = '<b>Flat No.</b> ' . $data->flat_no . ', ';
        $flat_data_string .= '<b>Flat Type-</b> ' . $data->flat_type . ', ';
        $flat_data_string .= '<b>Estate Name-</b> ' . $data->estate_name . ', ';
        $flat_data_string .= '<b>Estate Address-</b> ' . $data->estate_address . ' ,' . $data->district_name;
        $fields[] = $flat_data_string;

        $rows[] = $fields;
        $i++;
    }

    if($result->rowCount() > 0) { 
        $variables = array(
          'header' => $header,
          'rows' => $rows,
          'attributes' => array('class'=>array('table table-striped')),
        );
        
        $output = '<br>'.theme('datatable', $variables);
    }
    return $output;   
}
