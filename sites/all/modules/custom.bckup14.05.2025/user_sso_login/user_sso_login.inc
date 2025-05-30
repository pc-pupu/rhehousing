<?php
function user_sso_login($form, &$form_state, $userHRMSID)
{

    global $user;

    if (isset($user->uid) && !empty($user->uid))
    {
        
        //Print "This message is only visible for logged-in users.";
        // $form_state['redirect'] = 'user/' . $user->uid;
        $form_state['redirect'] = 'dashboard';
    }
    else
    {
        $userHRMSID = base64_decode($userHRMSID); 
        $userData = getHRMSUserData($userHRMSID);
        if (!empty($userData))
        {
            // print_r($userData);
            // echo $userData['hrmsId'];
            // exit();
            $query = db_select('users', 'u');
            // $query->join('housing_applicant', 'ha', 'ha.uid = u.uid');
            // $query->join('housing_applicant_official_detail', 'haod', 'haod.uid = u.uid');
            $query->addField('u', 'mail');
            $query->fields('u', array(
                'uid',
                'name',
                'mail'
            ));
            // $query->fields('ha', array(
            //     'applicant_name',
            //     'date_of_birth',
            //     'mobile_no',
            //     'gender'
            // ));
            // $query->fields('haod', array(
            //     'hrms_id',
            //     'office_name',
            //     'applicant_designation'
            // ));
            $query->condition('u.name', $userData['hrmsId']);
            // $query->condition('haod.hrms_id', $userData['hrmsId']);
            $userDetails = $query->execute()
                ->fetchObject();

            $transaction = db_transaction();
            try
            {
                if (empty($userDetails))
                {
                    //echo "llll";die;
                    $mail = isset($userData['email']) ? trim($userData['email']) : $userData['hrmsId'].'@gmail.com';
                   
                    $appUserData = array(
                        'name' => trim($userData['hrmsId']) ,
                        'pass' => trim($userData['hrmsId']) , // note: do not md5 the password
                        'mail' => $mail,
                        'access' => REQUEST_TIME,
                        'login' => REQUEST_TIME,
                        'status' => 1,
                        //'init' => trim($userData['email']),
                        'roles' => array(
                            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
                            4 => 'Applicant'
                        )
                    );
                    if (isset($userData['email']) && !empty($userData['email']))
                    {
                        $appUserData['mail'] = trim($userData['email']);
                        $appUserData['init'] = trim($userData['email']);
                    }
                    // The first parameter is sent blank so a new user is created.
                    $userDetails = user_save(Null, $appUserData);


                    ////////////////////turned off by debaleena 18-11-2024/////////
                    /*insert into housing_applicant table*/
                    // $user_reg_arr = array();
                    // $user_reg_arr['uid'] = $userDetails->uid;
                    // $user_reg_arr['applicant_name'] = strtoupper(trim($userData['applicantName']));
                    // $user_reg_arr['gender'] = (strtoupper(trim($userData['gender'])) == 'MALE') ? 'M' : 'F';
                    // $user_reg_arr['date_of_birth'] = date("Y-m-d", strtotime(trim($userData['dateOfBirth'])));
                    // $user_reg_arr['mobile_no'] = trim($userData['mobileNo']);
                    // db_insert('housing_applicant')->fields($user_reg_arr)->execute();

                    // /*insert into housing_applicant_official_detail table*/
                    // $app_off_detail_arr = array();
                    // $app_off_detail_arr['uid'] = $userDetails->uid;
                    // $app_off_detail_arr['hrms_id'] = trim($userData['hrmsId']);
                    // $app_off_detail_arr['applicant_designation'] = strtoupper(trim($userData['applicantDesignation']));
                    // $app_off_detail_arr['office_name'] = strtoupper(trim($userData['officeName']));
                    // //echo "<pre>";print_r($app_off_detail_arr);die;
                    // db_insert('housing_applicant_official_detail')->fields($app_off_detail_arr)->execute();
                    //////////////////end/////////////////////

                }
                else
                {
                    //echo "kkk";die;
                    //echo $userData['email'];die;
                    $updateUserData = array(
                        'login' => REQUEST_TIME
                    );
                    if (isset($userData['email']) && !empty($userData['email']))
                    {
                       if ($userDetails->mail != trim($userData['email']))
                        {
                            $updateUserData['mail'] = trim($userData['email']);
                        }
                    }
                    db_update('users')->fields($updateUserData)->condition('uid', $userDetails->uid)
                        ->execute();
                    //turned off by debaleena 18-11-2024////
                    /*update housing_applicant table*/
                    // $updateApplicantData = array();
                    // if ($userDetails->mobile_no != trim($userData['mobileNo']))
                    // {
                    //     $updateApplicantData['mobile_no'] = trim($userData['mobileNo']);
                    // }
                    
                    // if (count($updateApplicantData) > 0)
                    // {
                    //     db_update('housing_applicant')->fields($updateApplicantData)->condition('uid', $userDetails->uid)
                    //         ->execute();
                    // }
                }
                $user = user_load($userDetails->uid);
                // $form_state['redirect'] = 'user/' . $userDetails->uid;
                watchdog('user', 'Session opened for %name.', array(
                    '%name' => $userDetails->name
                ));
                drupal_session_regenerate();
                $form_state['redirect'] = 'dashboard';
            }
            catch(Exception $e)
            {
                // One of the INSERTs failed, rollback the whole batch.
                $transaction->rollback();
                // Rethrow the exception for the calling code.
                //throw $e;
                watchdog_exception('sso_login_reg', $e);
                // drupal_set_message(t($e) , 'error');
                drupal_set_message(t('Something went wrong! Please contact administration.') , 'error');
            }
        }
        else
        {
            watchdog('new_application', 'Error: HRMS NO User Data fetched. ID: ' . $userHRMSID);
            drupal_set_message(t('Error: HRMS NO User Data fetched.') , 'error');
            $form_state['redirect'] = '';
            drupal_goto();
        }
    }
    //drupal_goto("products", array('fragment' => $node->nid));
    drupal_goto($form_state['redirect']);
    // Regenerate the session ID to prevent against session fixation attacks.
    // This is called before hook_user in case one of those functions fails
    // or incorrectly does a redirect which would leave the old session in place.
}

function user_ddo_login($form, &$form_state, $ddocode){
    global $user;

    if (isset($user->uid) && !empty($user->uid))
    {
        $form_state['redirect'] = 'dashboard';
    }
    else
    {
        
        $ddocode = base64_decode($ddocode);
        $user = user_load_by_name($ddocode);
        $user_id = $user->uid; 

        $updateUserData = array(         'login' => REQUEST_TIME );
        db_update('users')->fields($updateUserData)->condition('uid', $user_id)->execute();

        $account = user_load($user_id, TRUE); 
        // drupal_session_regenerate();

        $form_state['redirect'] = 'dashboard';

        // drupal_goto('dashboard');

    }
    drupal_goto($form_state['redirect']);
}