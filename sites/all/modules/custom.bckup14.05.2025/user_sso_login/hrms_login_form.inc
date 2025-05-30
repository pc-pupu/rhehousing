<?php
function hrms_login_form($form, &$form_state) {
    if(!user_is_logged_in()) {

        $form['markup_header'] = array(
            '#type' => 'markup',
            '#markup' => '<div class="d-flex justify-content-center h-100 end-0"><div class="search">'
        );

        $form['name'] = array(
            '#type' => 'item',
            '#prefix' => '<div id="hrms" class="login-panel">',
            '#suffix' => '</div>',
        );
        $form['name']['hrms_id'] = array(
            '#type' => 'textfield',
            '#required' => TRUE,
            '#attributes' => array('class'=>array('search_input'), 'placeholder'=> 'Enter HRMS ID'),	
            // '#title' => t('Enter HRMS Id'),
        );
        $form['name']['submit'] = array(
            '#type' => 'submit',
            '#attributes' => array('class'=>array('search_icon')),
            '#value' => 'Go',
        );
        // $form['rhe_user_login'] = array(
        //     '#type'    => 'link',  
        //     '#prefix' => '<div class="m-3">',
        //     '#suffix' => '</div>',  
        //     '#title'   => t('Click here for Housing users login'),    
        //     '#href'  => '/user/login',
        //     '#attributes' => array('class' => array('btn btn-light btn-sm')),
        
        // );
        $form['markup_footer'] = array(
            '#type' => 'markup',
            '#markup' => '</div></div>'
        );
        return $form;
    } else { 
        // die('ekhanei dhukche');
        // drupal_goto('/user');
        drupal_goto('dashboard');
    }
    
}

function hrms_login_form_submit($form, &$form_state) {
    if(isset($form_state['values']['hrms_id']) && !empty($form_state['values']['hrms_id'])) {
        $hrms_id = base64_encode(trim($form_state['values']['hrms_id']));
        
        drupal_goto('/user/sso/' . $hrms_id);

    }
}
?>