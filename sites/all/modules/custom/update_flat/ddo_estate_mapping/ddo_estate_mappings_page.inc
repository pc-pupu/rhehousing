<?php
function fss_price_list_page()
{
    //$build['search_form'] = drupal_get_form('indent_entry_form');
    //drupal_render($build);
    $build['details_form'] = drupal_get_form('ddo_estate_mapping_list');
    return $build;
}

function ddo_estate_mapping_list($form, &$form_state)
{
    global $base_path;
    //drupal_add_js(drupal_get_path('module', 'product') .'/js/print.js');
    ctools_include('modal');
    ctools_modal_add_js();
    
    ctools_include('ajax');
    ctools_add_js('ajax-responder');
    
    // Initialising output
    $output = '';
    
    // Table header
    $header    = array(
        'slno' => array(
            'data' => 'Sl. No.'
        ),
        'district_name' => array(
            'data' => 'District Name'
        ),
        'ddo_designation' => array(
            'data' => 'DDO Designation'
        ),
        'ddo_address' => array(
            'data' => 'DDO Address'
        ),
        'estate_name' => array(
            'data' => 'Estate Name'
        ),
        'estate_address' => array(
            'data' => 'Estate Address'
        ),
        'created_date' => array(
            'data' => 'Created Date'
        ),
       /* 'operations' => array(
            'data' => 'OPERATION'
        )*/
    );
    $rows      = array();
    $row_count = 0;
    $query = db_select('housing_ddo_estate_mappings', "t1");
    $query->join('housing_ddo_all', "t2", 't1.ddo_id= t2.ddo_id');
    $query->join('housing_district', "t4", 't2.district_code= t4.district_code');
    $query->join('housing_estate', "t3", 't1.estate_id= t3.estate_id');
    $query->fields('t1');
    $query->fields('t2');
    $query->fields('t3');
    $query->fields('t4');
    $query->orderBy('t1.created', 'DESC');
    // Executing query
    $result = $query->execute();
    
    // Looping for filling the table rows
    $page   = 0;
    
    
    //$src  = $base_path . drupal_get_path('module', 'fss_management_kitbank') . '/images/view.png';
    
    while ($data = $result->fetchObject()) {
        /*$operation_link = NULL;
        $view_link      = l('<img src="' . $src . '" width="24">', 'view-fss-breed-price/nojs/' . base64_encode($data->id), array(
            'html' => TRUE,
            'attributes' => array(
                'class' => 'ctools-use-modal'
            )
        ));
        $operation_link .= $view_link . ' &nbsp;&nbsp;';*/
        
        $row_count++;
        
        $rows[$data->id] = array(
            'data' => array(
                'slno' => array(
                    'data' => $row_count,
                    'data-id' => $data->id
                ),
                'district_name' => array(
                    'data' => $data->district_name
                ),
                'ddo_designation' => array(
                    'data' => $data->ddo_designation
                ),
                'ddo_address' => array(
                    'data' => $data->ddo_address
                ),
                'estate_name' => array(
                    'data' => $data->estate_name
                ),
                'estate_address' => array(
                    'data' => $data->estate_address
                ),
                'created_date' => array(
                    'data' => $data->created,
                    'style' => 'vertical-align: middle'
                ),
                /*'operations' => array(
                    'data' => $operation_link,
                    'style' => 'vertical-align: middle'
                )*/
            ),
            'data-indent-ref' => $data->id
        );
    }
    // Or, render using a theme function.
    $variables = array(
        //'attributes' => array('id' => 'divToPrint'),
        'header' => $header,
        'rows' => $rows,
        'caption' => '<h2>Show All Mappings</h2>',
        'sticky' => FALSE,
        'empty' => 'No data found!'
    );
    
    //$output = theme('datatable', $variables);
    $output = theme('table', $variables);
    
    $current_url = getenv('REQUEST_URI');

    $html= NULL;
    if (user_access('administer add ddo estate mapping')){ 
        $html = '<ul><li>'.ctools_modal_text_button('<b class="add-dt-btn">Add New Mapping</b>', 'add-ddo-estate-mapping/nojs', 'Add New Mapping').'</li>';
    }
    
   
    $form['table'] = array(
        '#markup' => '<br>'.$html . $output
        //'#markup' => '<br>'.$html
    );
    return $form;
}

?>