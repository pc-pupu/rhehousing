<?php // Done by Subham 05-06-2024
function user_profile_form($form, &$form_state) {
    global $user, $user_role;

    $roleArr = $user->roles;
    $usr_role = $roleArr[$user_role];
    // print_r($user);die;

    $get_hrms_data = getHRMSUserData($user->name);
    
    /************ dg 30-12-2024 ***********/

        $query = db_select('housing_applicant', 'ha');

        //$query->innerJoin('housing_applicant_official_detail', 'haod', 'ha.uid = haod.uid');  //off by dg 30-12-2024
        $query->innerJoin('housing_applicant_official_detail', 'haod', 'ha.housing_applicant_id = haod.housing_applicant_id');  //added by dg 30-12-2024 
        $query->innerJoin('housing_online_application', 'hoa', 'hoa.applicant_official_detail_id = haod.applicant_official_detail_id');
        $query->leftJoin('housing_flat_occupant', 'hfo', 'hfo.online_application_id = hoa.online_application_id');
        $query->leftJoin('housing_flat', 'hf', 'hf.flat_id = hfo.flat_id');
        $query->leftJoin('housing_block', 'hb', 'hf.block_id = hb.block_id');
        $query->leftJoin('housing_estate', 'he', 'he.estate_id = hf.estate_id');
        $query->leftJoin('housing_flat_type', 'hft', 'hft.flat_type_id = hf.flat_type_id');
        $query->innerJoin('users', 'u', 'u.uid = haod.uid');
        $query->condition('haod.uid', $user->uid, '=');
        $query->condition('haod.is_active', '1', '=');

        $query->addField('ha', 'applicant_name');
        $query->addField('ha', 'guardian_name');
        $query->addField('ha', 'permanent_street');
        $query->addField('ha', 'permanent_city_town_village');
        $query->addField('ha', 'permanent_post_office');
        $query->addField('ha', 'permanent_pincode');
        $query->addField('ha', 'mobile_no');
        $query->addField('he', 'estate_name');
        $query->addField('he', 'estate_address');
        $query->addField('hft', 'flat_type');
        $query->addField('hf', 'floor');
        $query->addField('hf', 'flat_no');
        $query->addField('hb', 'block_name');
        $query->addField('haod', 'hrms_id');
        $query->addField('u', 'status');
        // echo $query;die;

        $result =$query->execute()->fetchObject();
        // print_r($result);die;

        //$applicant_name = isset($get_hrms_data['applicantName']) ? $get_hrms_data['applicantName'] : 'N/A';
        $applicant_name = (isset($usr_role) && ($usr_role != 'Applicant' && $usr_role != 'Occupant') ? $usr_role : (isset($get_hrms_data['applicantName']) ? ucwords(strtolower($get_hrms_data['applicantName'])) : 'N/A'));

        $guardian_name = isset($get_hrms_data['guardianName']) ? $get_hrms_data['guardianName'] : (isset($result->guardian_name) ? ucwords(strtolower($result->guardian_name)) : 'N/A');

        $parmanent_address_hrms = implode(', ', array_filter([
                !empty($get_hrms_data['permanentStreet']) ? $get_hrms_data['permanentStreet'] : '',
                !empty($get_hrms_data['permanentCityTownVillage']) ? $get_hrms_data['permanentCityTownVillage'] : '',
                !empty($get_hrms_data['permanentPostOffice']) ? $get_hrms_data['permanentPostOffice'] : '',
                !empty($get_hrms_data['permanentPincode']) ? $get_hrms_data['permanentPincode'] : ''
        ]));
        $parmanent_address_db = implode(', ', array_filter([
            !empty($result->permanent_street) ? $result->permanent_street : '',
            !empty($result->permanent_city_town_village) ? $result->permanent_city_town_village : '',
            !empty($result->permanent_post_office) ? $result->permanent_post_office : '',
            !empty($result->permanent_pincode) ? $result->permanent_pincode : ''
        ]));
        // echo $parmanent_address_db;die;
        
        $parmanent_address = !empty($parmanent_address_hrms) ? ucwords(strtolower($parmanent_address_hrms)) : (isset($parmanent_address_db) && !empty($parmanent_address_db) ? ucwords(strtolower($parmanent_address_db)) : 'N/A');

        $mobile_no = isset($get_hrms_data['mobileNo']) ? $get_hrms_data['mobileNo'] : (isset($result->mobile_no) ? ucwords(strtolower($result->mobile_no)) : 'N/A');

        $email = !empty($user->mail) ? $user->mail : (!empty($get_hrms_data['email']) ? $get_hrms_data['email'] : 'N/A');

        
       
        $output = '<div class="table-bottom">
                <table class="table table-list">
                    <tr>
                        <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family:Arial,Verdana,serif;" class="first">Personal Details</th>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Applicant Name : </th>
                        <td width="50%">'.$applicant_name.'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Guardian Name : </th>
                        <td width="50%">'.$guardian_name.'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Parmanent Address : </th>
                        <td width="50%">'.$parmanent_address.'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Mobile No : </th>
                        <td width="50%">'.$mobile_no.'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Email : </th>
                        <td width="50%">'.$email.'</td>
                    </tr>
                    <tr>
                        <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px;font-weight: normal;font-family:Arial,Verdana,serif;" class="first">Flat Allotment Details</th>
                    </tr>
                     <tr>
                        <th style="background-color:#00000000" width="50%">Estate Name : </th>
                        <td width="50%">'. (isset($result->estate_name) ? $result->estate_name : 'N/A').'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Estate Address : </th>
                        <td width="50%">'.(isset($result->estate_address) ? $result->estate_address : 'N/A').'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Block Name : </th>
                        <td width="50%">'.(isset($result->block_name) ? $result->block_name : 'N/A').'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Flat Type : </th>
                        <td width="50%">'.(isset($result->flat_type) ? $result->flat_type : 'N/A').'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Flat No : </th>
                        <td width="50%">'.(isset($result->flat_no) ? $result->flat_no : 'N/A').'</td>
                    </tr>
                    <tr>
                        <th style="background-color:#00000000" width="50%">Floor : </th>
                        <td width="50%">'.(isset($result->floor) ? $result->floor : 'N/A').'</td>
                    </tr>
                </table>
        
        </div>
        ';


    /*********end  ******/



    $form['markup_data'] = array(
        '#type' => 'markup',
        '#markup' => $output
    );

    return $form;
}
