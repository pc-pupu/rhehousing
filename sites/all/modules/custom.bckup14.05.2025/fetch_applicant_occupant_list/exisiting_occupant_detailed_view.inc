<?php
function existing_occupant_detailed_view_form($app_id = 0){
    $dec_app_id = decrypt_url($app_id);
    $query = "SELECT hoa.application_no, ha.applicant_name, haod.applicant_designation, he.estate_name, he.estate_address, hft.flat_type, 
              hf.floor, hf.flat_no, hf.block_id, hb.block_name
              FROM housing_online_application hoa
              INNER JOIN housing_applicant_official_detail haod ON hoa.applicant_official_detail_id = haod.applicant_official_detail_id
              INNER JOIN housing_applicant ha ON ha.uid = haod.uid
              INNER JOIN housing_flat_occupant hfo ON hfo.online_application_id = hoa.online_application_id
              INNER JOIN housing_flat hf ON hf.flat_id = hfo.flat_id
              INNER JOIN housing_estate he ON he.estate_id = hf.estate_id
              INNER JOIN housing_flat_type hft ON hft.flat_type_id = hf.flat_type_id
              INNER JOIN housing_block hb ON hf.block_id = hb.block_id
              WHERE hoa.application_no = '$dec_app_id'";
    $result = db_query($query);
    $output = $result->fetchAssoc();
    
    $display_output1 = '
    <div class="table-bottom">
        <table class="table table-list">
          <tr>
            <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px; font-weight: normal;font-family: "Dosis",Arial,Verdana,serif;" class="first">Application Information</th>
          </tr>
          <tr>
            <th style="background-color:#00000000" width="50%">Application Number:</th>
            <td width="50%">'.$output['application_no'].'</td>
          </tr>'
          // <tr>
          //   <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px; font-weight: normal;font-family: "Dosis",Arial,Verdana,serif;" class="first">Applicant Personal Information (According to Service Book)</th>
          // </tr>
          .'
          <tr>
            <th style="background-color:#00000000">Applicant\'s Name:</th>
            <td>'.$output['applicant_name'].'</td>
          </tr>'
          // <tr>
          //   <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px; font-weight: normal;font-family: "Dosis",Arial,Verdana,serif;" class="first">Applicant Official Information</th>
          // </tr>
          .'
          <tr>
            <th style="background-color:#00000000">Designation:</th>
            <td>'.$output['applicant_designation'].'</td>
          </tr>
          <tr>
            <th colspan="2" style="background: none repeat scroll 0 0 #473a39;color:white;text-align: center;font-size: 18px;line-height: 24px; font-weight: normal;font-family: "Dosis",Arial,Verdana,serif;" class="first">Information for Allotment</th>
          </tr>
          <tr>
            <th style="background-color:#00000000">Estate Name:</th>
            <td>'.(isset($output['estate_name']) ? $output['estate_name'] : 'N/A').'</td>
          </tr>
          <tr>
            <th style="background-color:#00000000">Estate Address:</th>
            <td>'.(isset($output['estate_address']) ? $output['estate_address'] : 'N/A').'</td>
          </tr>
          <tr>
            <th style="background-color:#00000000">Flat Type:</th>
            <td>'.(isset($output['flat_type']) ? $output['flat_type'] : 'N/A').'</td>
          </tr>
          <tr>
            <th style="background-color:#00000000">Floor:</th>
            <td>'.(isset($output['floor']) ? $output['floor'] : 'N/A').'</td>
          </tr>
          <tr>
            <th style="background-color:#00000000">Flat Number:</th>
            <td>'.(isset($output['flat_no']) ? $output['flat_no'] : 'N/A').'</td>
          </tr>
          <tr>
            <th style="background-color:#00000000">Block Name:</th>
            <td>'.(isset($output['block_name']) ? $output['block_name'] : 'N/A').'</td>
          </tr>
        </table>
    </div>';
    return $display_output1;
}