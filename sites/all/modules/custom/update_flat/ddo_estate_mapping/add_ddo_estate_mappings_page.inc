<?php
function add_fss_price_page($ajax)
{
    if ($ajax) {
        ctools_include('ajax');
        ctools_include('modal');
        $form_state      = array(
            'ajax' => TRUE,
            'title' => t('Add DDO Estate Mapping'),
            //'wildcard' => $fssIndentResult
        );
        // Use ctools to generate ajax instructions for the browser to create
        // a form in a modal popup.
        $output          = ctools_modal_form_wrapper('add_housing_ddo_estate_mapping', $form_state);
        
        // If the form has been submitted, there may be additional instructions
        // such as dismissing the modal popup.
        if (!empty($form_state['ajax_commands'])) {
            $output = $form_state['ajax_commands'];
        }
        // Return the ajax instructions to the browser via ajax_render().
        print ajax_render($output);
        drupal_exit();
    } else {
        return drupal_get_form('add_housing_ddo_estate_mapping');
    }
}

function add_housing_ddo_estate_mapping($form, &$form_state)
{
    global $user_role;
    global $fssSrcTypes;
    /*global $user_kitbank_id;
    global $user_dist_code;
    global $user_block_code;*/

    $form['ddo'] = array(
        '#type' => 'fieldset',
        '#title' => t('Add DDO Estate Mapping From'),
        //'#attributes' => array('class' => array('container-inline')),
        //'#collapsible' => TRUE, // Added
        //'#collapsed' => TRUE,  // Added
    );

    
        $form['ddo']['district'] = array(
            '#title' => t('DDO District'),
            '#type' => 'select',
            '#options' => district_list(),
            '#disabled' => TRUE,
            '#ajax' => array(
                       'event' => 'change',
                       'callback' => '_reload_ddo_flat_designation',
                      // 'wrapper' => 'replace_designation',
                       'effect' => 'fade',
                       'progress' => array(
                          'type' => '',
                          'message' => '',
                        ), 
             ),
            '#required' => TRUE,
            '#validated' => TRUE,
            '#prefix' => '<div class="two">',
            '#suffix' => '</div>',
            '#select2' => array(
                'width' => '500',
                //'placeholder' => '- Select -',
                'allowClear' => TRUE
            )
        );
        
        
        $form['ddo']['designation'] = array(
            '#title' => t('DDO Designation'),
            '#empty' => '-- Choose DDO Designation --',
            '#type' => 'select',
            //'#options' => array('- Select -'),
            '#options' => ddo_desig_list_cus($district),
           '#ajax' => array(
                       'event' => 'change',
                       'callback' => '_reload_ddo_address',
                       'wrapper' => 'replace_ddo_address',
                       'effect' => 'fade',
                       'progress' => array(
                          'type' => '',
                          'message' => '',
                         ),
             ),
            //'#default_value' => $designation,
            '#required' => TRUE,
            '#validated' => TRUE,
            '#prefix' => '<div id="replace_designation" class="two">',
            '#suffix' => '</div>',
            '#select2' => array(
                'width' => '500',
                'placeholder' => '-- Choose DDO Designation --',
                'allowClear' => TRUE
            )
        );
        
        $form['ddo']['address'] = array(
            '#title' => t('DDO Address'),
            '#type' => 'textarea',
            '#attributes' => array('readonly' => 'readonly'),
            '#prefix' => '<div id="replace_ddo_address" class="two">',
            '#suffix' => '</div>',
            //'#required' => TRUE,
            //'#validated' => TRUE,
        );
        $form['ddo']['occupation_estate'] = array(
            '#title' => t('Select Housing (Multiple)'),
            '#type' => 'select',
            '#empty' => '- ALL -',
            '#multiple' => TRUE,
            '#options' => get_housing_estate_cus($district),
            //'#default_value' => $occupation_estate,
            '#required' => TRUE,
           /* '#ajax' => array(
                           'event' => 'change',
                           'callback' => '_reload_block_no_vs',
                           'effect' => 'fade',
                           'progress' => array(
                              'type' => '',
                              'message' => '',
                            ),
                ),*/
            '#prefix' => '<div id="replace_estate" class="two">',
            '#suffix' => '</div>',
            '#validated' => TRUE,
            '#select2' => array(
                'width' => '500',
                //'placeholder' => '- Select -',
                'allowClear' => TRUE
            )
        );
    
    $form['ddo']['submit'] = array(
        //'#suffix' => '</div>',
        '#type' => 'submit',
        '#value' => t('Add New Mapping')
    );
    
    return $form;
}

/*function add_housing_ddo_estate_mapping_validate($form, &$form_state)
{
    
    if (!empty($fssBreedPriceEntry)) {

        foreach ($fssBreedPriceEntry as $animalBreedId) {
            $animalBreedId = trim($animalBreedId);
            if ($animalBreedId != '0') {
                $updateAccessoriesID[] = $animalBreedId;
                if (!checkVaildNumeric($form_state['input']['breed_price'][$animalBreedId])) {
                    $errorMSG .= 'Invaild No of Breed Found REF: ' . $form_state['input']['breed_price'][$animalBreedId] . '<br>';
                }
            }
        }
        $varRec = count($updateAccessoriesID);
        
        if ($varRec == 0) {
            form_set_error('', t('No Breed Selected'));
        } elseif (!empty($errorMSG)) {
            form_set_error('', t($errorMSG));
        }
    } else {
        $varMsg = 'No Breed Selected';
        form_set_error('', t($varMsg));
    }
}*/

function add_housing_ddo_estate_mapping_submit($form, &$form_state)
{
    global $user;
    global $fssSrcTypes;
    
    $ddoEstateInsertData = array();
    $createdDate          = date('Y-m-d');
    
    $transaction = db_transaction();
    try {
        $ddoEstateMappingInsert = db_insert('housing_ddo_estate_mappings')->fields(array(
            'ddo_id',
            'estate_id',
            'created_uid',
            'created'
        ));
        foreach ($form_state['values']['occupation_estate'] as $occupationEstate) {
                if (!empty($occupationEstate) && $occupationEstate > 0) {
                    $ddoEstateInsertData = array(
                        'ddo_id' => $form_state['values']['designation'],
                        'estate_id' => $occupationEstate,
                        'created_uid' => $user->uid,
                        'created' => $createdDate,
                    );
                    $ddoEstateMappingInsert->values($ddoEstateInsertData);
                }
        }
        
        if (!empty($ddoEstateInsertData)) {
            $ddoEstateMappingInsert->execute();
        }

        $form_state['rebuild'] = TRUE;
        drupal_set_message(t("DDO Estate Mapping added Successfully."));
        $output[] = ctools_modal_command_dismiss(); //Close modal automatically
        $output[] = ctools_ajax_command_reload(); //reload parent window 
        // Return the ajax instructions to the browser via ajax_render().
        print ajax_render($output);
        drupal_exit();
    }
    catch (Exception $e) {
        // One of the INSERTs failed, rollback the whole batch.
        $transaction->rollback();
        // Rethrow the exception for the calling code.
        //throw $e;
        watchdog_exception('fss_management', $e);
        drupal_set_message(t($e), 'error');
    }
}
/*reload DDO designation list (Ajax Call)*/
    function _reload_ddo_flat_designation($form, &$form_state) {
        
        $district = isset($form_state['values']['district']) && !empty($form_state['values']['district']) ? $form_state['values']['district'] : '';
        
        $form['ddo']['address']['#value'] = '';
        if($district == '') {
            $form['ddo']['designation']['#options'] = array(''=>'- Select -');
            $form['ddo']['occupation_estate']['#options'] = array(''=>'- Select -');
        }
        else {
            $form['ddo']['designation']['#options'] = ddo_desig_list_cus($district);
            $form['ddo']['occupation_estate']['#options'] = get_housing_estate_cus($district);
        }
        $commands = array();
        $commands[] = ajax_command_replace('#replace_ddo_address', drupal_render($form['ddo']['address']));
        $commands[] = ajax_command_replace('#replace_designation', drupal_render($form['ddo']['designation']));
        $commands[] = ajax_command_replace('#replace_estate', drupal_render($form['ddo']['occupation_estate']));
        $form_state['rebuild'] = TRUE;
        return array('#type' => 'ajax', '#commands' => $commands);
    }

    /*reload DDO address (Ajax Call)*/
 function _reload_ddo_address1($form, &$form_state) {
     $ddo = isset($form_state['values']['designation']) && !empty($form_state['values']['designation']) ? $form_state['values']['designation'] : '';
     $form['ddo']['address']['#value'] = ddo_add($ddo);
     $form['ddo']['address']['#attributes']['readonly'] = 'readonly';
     $commands = array();
     $commands[] = ajax_command_replace('#replace_ddo_address', drupal_render($form['ddo']['address']));
     return array('#type' => 'ajax', '#commands' => $commands);
 
}

function get_housing_estate_cus($district) {
    
    //$housing_estate_arr = array(''=>'-- Select --');
    $housing_estate_arr = array();
    
    $query=db_select('housing_estate','he');
    $query->fields('he',array('estate_id','estate_name'));
    $query->condition('district_code', $district);
    $query->orderBy('estate_name', 'ASC');
    $result=$query->execute();
    
    foreach($result as $val) {
        $housing_estate_arr[$val->estate_id] = $val->estate_name;
    }
    
    return $housing_estate_arr;
    
}

function ddo_desig_list_cus($district = NULL) {
        
        $district = trim($district);    
        //$ddo_desig_options = array();
        $ddo_desig_options = array(''=>'-- Select --');
        if(!empty($district)) {
            $query = db_select('housing_ddo', 'hd');
            $query->leftJoin('housing_ddo_estate_mappings', "t2", 'hd.ddo_id= t2.ddo_id');
            $query->fields('hd', array(
                'ddo_id',
            ));
            $query->addExpression('trim(hd.ddo_designation)','ddo_designation');
            $query->condition('hd.district_code', $district, '=');
            $query->isNull('t2.id');
            $query->orderBy('ddo_designation', 'ASC');
            $query->orderBy('ddo_type_id', 'ASC');
            $result = $query->execute();
            //$result = db_query("select * from {housing_district} order by district_code");
        
            foreach($result as $val) {
                $ddo_desig_options[$val->ddo_id] = $val->ddo_designation;
            }
        }
        
        return $ddo_desig_options;
    }