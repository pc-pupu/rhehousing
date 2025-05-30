<?php 
// Done by Subham dt.07-08-2024
function licence_pdf_gen($app_id = '') {
    global $base_path, $base_root;
    $app_id= decrypt_url($app_id);
    $today_date = date('d-m-y');
    $fetch_applicant_details = fetch_applicant_details($app_id);
    // /print_r($fetch_applicant_details);die;

    /*~~~~~~~~~~~~~~~~~~~~~ QR Code Generation Code Starts Here ~~~~~~~~~~~~~~~~~~~*/

    $PNG_TEMP_DIR = drupal_get_path('module','view_application_list').'/phpqrcode/upload/license_qr_code/';
    $PNG_WEB_DIR = drupal_get_path('module','view_application_list').'/phpqrcode/upload/license_qr_code/';

    include "./sites/all/modules/custom/view_application_list/phpqrcode/qrlib.php";

    if (!file_exists($PNG_TEMP_DIR))
    mkdir($PNG_TEMP_DIR);

    $filename = $PNG_TEMP_DIR.'test.png';
    $errorCorrectionLevel = 'H';
    $matrixPointSize = 2;
    $qr_content = 'Name- '.$fetch_applicant_details->applicant_name.', License No.-'.$fetch_applicant_details->license_no.', Flat Number- '.$fetch_applicant_details->flat_no.', Flat Type- '.$fetch_applicant_details->flat_type.', RHE Name- '.$fetch_applicant_details->estate_name.', Flat Address- '. $fetch_applicant_details->estate_address;

    $filename = $PNG_TEMP_DIR.time().'.png';

    QRcode::png($qr_content, $filename, $errorCorrectionLevel, $matrixPointSize, 4); 

    $generate_qr_image = $PNG_WEB_DIR.basename($filename);


    $img_data = base64_encode(file_get_contents(drupal_get_path('module','view_application_list') .'/phpqrcode/upload/license_qr_code/'. basename($filename)));
    $qr_image = '<img src="data:image/png;base64,' . $img_data . '" style="margin-top:20px width:110px; height:110px;" />';

    /*~~~~~~~~~~~~~~~~~~~~~ QR Code Generation Code Ends Here ~~~~~~~~~~~~~~~~~~~*/

    $page_output ='';
    $page_output .= '
    <div style="border-style: solid";>
        <h3 align="center" style="font-size:20px"><b>GOVERNMENT OF WEST BENGAL</b></h3>
        <h3 align="center">HOUSING DEPARTMENT</h3>
        <h4 align="center">Licence for the Occupation of Government Premises</h4>
        <p align="left">
            <b>
                License No.:&emsp;&emsp;'.$fetch_applicant_details->license_no.' &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Dated : '.$today_date.'
            </b><br>  
            Licence under section 4 of the West Bengal Government Premises (Regulation of Occupancy) Act, 1984 is hereby granted to <b>'.$fetch_applicant_details->applicant_name .'</b> for the occupation of 
            <b>Flat No: '.$fetch_applicant_details->flat_no.',  ('.$fetch_applicant_details->flat_type.'-Type) by way of Fresh Allotment at '.$fetch_applicant_details->estate_address.' R.H.E</b> subject to the provisions of the said Act and to the additional terms and conditions mentioned below.
            <ol style="font-size:0.85em">
                <li>The validity of this licence will expire on <b>'.date("d-m-Y",strtotime($fetch_applicant_details->license_expiry_date)).'</b></li>
                <li>Date Of Retirment</li>
            </ol>
            &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sd/-
            &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Competent Authority under the West Bengal
            &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;Government Premises (Regulation of Occupancy) Act, 1984
            <h3 align="center"><b>ADDITIONAL TERMS AND CONDITIONS</b></h3>
            <ol style="font-size:0.85em">
                <li>He will not draw H.R.A.</li>
                <li>He is requested to intimate this Department the date of possession of the flat.</li>
            </ol>
            &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Sd/-
            &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Competent Authority under the West Bengal
            &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&nbsp;Government Premises (Regulation of Occupancy) Act, 1984
        </p>
        <p align="left">
            <b>
                License No.&emsp;&emsp;&nbsp; '.$fetch_applicant_details->license_no.'&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;Dated: '.$today_date.'
            </b><br>
            Copy forwarded, for information and necessary action to:
        </P>
        <ol type="I" style="font-size:0.85em">
            <li><b>'.$fetch_applicant_details->applicant_name. ', '.$fetch_applicant_details->applicant_designation.'</b></li>
            <li><b>The Finance (Audit) Department, Nabanna, Howrah-711102.</b></li>
            <li><b>Section Officer & DDO, Finance Department (Accounts Branch), Nabanna, Howrah-711102.</b>
            (Head of office /D.D.O) He is requested to intimate this office regarding transfer/retiremnet of the licensee from the present posting.
            </li>
            <li>The Executive Engineer, Kolkata North-I Division, Flat Nos. D/1 & D/2,82, Belgachia Road R.H.E., Kolkata-700037</li>
            <li>The Executive Engineer, Electrical Division No.II,67, Bentinck Street, 3rd Floor, Kol-69.</li>
            <li>The Pay and Acoounts Officer, Kolkata Pay and A/cs.Office-II, P-1, Hyde lane,Kol-73.</li>
            <li>The Work Assistant, Rani Harshmukhi Road R.H.E.
            <br>It may be noted that the retirement of the license is on 31.01.2026.</li>
            <li>The Assistant Engineer, Kolkata North Sub-Division-II, P-1, Hyde Lane, Kol-37.</li>
            <li>The Computer Cell.</li>
        </ol>
        <p style="font-size:0.75em">
            2. Special attention is invited to clauses 10 and 11 of the terms and conditions mentioned overleaf. Pending receipt of roll for licence fee from the Executive Engineer, licence fee at the rate indicated under additional terms and conditions should be realised from the salary of the licensee and credited to the head "0216-Housing-02-Urban Housing-105-Receipts from Rental Housing scheme-001 collection for RHS-05-Rent". Code No.[0216-02-105-001-05].
        </p>
        <div style="display: flex; justify-content: space-between; align-items: center;">
        <div>'.$qr_image.'</div>
        <div style="text-align: right;">
            Competent Authority under the West Bengal<br>
            Government Premises (Regulation of Occupancy) Act, 1984
        </div>
        <br>
    <div>
        <h4 align="center"><b>Terms and conditions applicable to all licences in respect of Government Premises</b></h4>
        <ol style="font-size:0.75em">
            <li><font size="1">Subject to provisions of item 2 and section 11, a license shall remain valid for specified period and such period may be renewed from time by the competent Authority.For this purpose specified period shall mean-</font></li>
                <ol type="i">
                    <li><font size="1">the period specified in the liocense or, where nothing is specified in the license, a period of three years from the date of issue of license and such date, in the case of anything deemed to be a license under section 9, shall be the appointed day;or</font></li>
                    <li> <font size="1">any period for which the license is renewed by the Competent Authority.</font></li>
                </ol>
            <li><font size="1">An application for the renewal of a license shall be made to the Competent Authority in the prescribed manner. No such application shall be refeused by the Competent Authority if the licensee continues to be eligible to hold the license in accordance with the provision of this Act. A license shall remain valid during the pendency of an application for its renewal.</font></li>
            <li><font size="1">An application for the renewal of license shall state inter alia the licensee\'s post and place of posting.</font></li>
            <li><font size="1">A license shall cease to be valid if the licensee fails to take possesion of the premises covered by it (here in after referred to as the premises) within fifteen days of its issue or within such period as the competent Authority may grant, upon an application by the licensee.</font></li>
            <li><font size="1">The licencee shall use the premises for the purpose for which they have been allotted to him and shal not use them for any other purpose.<br>Example- where a flat is allotted to any person of the purpose of his residence there will be a violation of this condition if he does not himself ordinary, reside in it and allows his dependents or any other person to reside in it or keeps it vacant.</font></li>
            <li><font size="1">The licencee shall not assign or transfer the premises in any way to any person or put any person in possesission of the premises.</font></li>
            <li><font size="1">The licencee shall not add to, or alter, any fixtures of the premises or make any structural alterartions in the premises without the express permission in writting of the Competent Authoity.</font></li>
            <li><font size="1">The licencee shall not cause, or suffer to be caused, any damage to the premises beyond the normal wear and tear thrugh the proper use and occupation of the premises</font></li>
            <li><font size="1">The licencee shall allow any officer duly authorize in this behalf by the Competent Authority to inspect the premises as and when necessary.</font></li>
            <li><font size="1">The licencee shall pay such license fee for the premises as may be determined from time to time by the-Competent Authority.</font></li>
            <li><font size="1">The licencee fee in respect of each month shall be pyable by the first week if the following month in such manner as may be stipulated by the Copetent Auhority.
            <br>The licencee shall send to the Competent Authority as and when required by it a statement showing the details of the license fee paid by the license, and such statement shall be in such form, and shall be authenticated in such manner, as may be stipulated by the Competent Authoriy.</font></li>
            <li><font size="1">The licencee, if he is occupation of Government premises on the appointed day, shall inform the Competent Authority in Writing within one month from that day about the post held by him,the headquarters of his post and the date of his retirement on superannuation based upon entries contained in his Service Book.</li>
            <li><font size="1">The licencee shall inform the Competent Authority in writing about every change in his post o place of posting and every chnge in his is by reason of his going on leave, or being oplaced under suspension or by any other reason within a week of the change taking place.</font></li>
            <li><font size="1">A license may be terminated upon--
                <ol type="a">
                <li><font size="1">the acquistion of licencee of any other premises by way of ownership,tenancy or otherwise either in his own name or in the name of any member of family dependent on him.</font></li>
                <li><font size="1">the violation by the licensee of any of the terms and conditions of the license;
                <li><font size="1">the licencee being placed under suspension, or upon proceeding on leave of any kind, for a period exceeding six months:<br>Provided that where, by reson of any declaration made under section 5, that post from which the license has proceeded on leave is a specified post in respect of the premises occupied by him and authority granting the leave has not certified that upon the expiry of the leave the licencee is likely to return to that post, the license may be terminated at any time after the commencement of the leave;</font></li>
                <li><font size="1">the expiry of one calendar month\'s notice given by the competent Authority to the licensee.</font></li></ol>
                <li><font size="1">Upon the expiry or termination of any license, the licencee shall deliver vacant possession of the premises to the competent Authority,or to any other person authorised by the Competent Authority in this behalf, in the sme condition in which the licencee took possession of the premises.</font></li>
            <li><font size="1">
                The license shall automatically terminated upon:
                <ol type="i"><li><font size="1">The death of the licensee or </font></li><li><font size="1">the expiry of the period of validity of the license or</font></li>
                    <li><font size="1">the cessation of the licensee\'s employment under the state Government by reason of his retirement, resignation, discharge or dismissal or by any other reason,or</font></li>
                    <li><font size="1">the licensee ceasing to hold any specified post under the state Government by reason of his transfer from any such post on any other reason.</font></li>
                </ol>
            </li>
        </ol>
    </div>';

	ob_end_clean();
    $file_name = '';
    return pdf_using_mpdf_api($page_output, $file_name);
}


/* debaleena start 08-08-2024 */

function fetch_applicant_details($app_id = ''){
    $query = db_select('housing_online_application', 'hoa');
	$query->innerJoin('housing_flat_occupant', 'hfo','hfo.online_application_id = hoa.online_application_id');
	$query->innerJoin('housing_applicant_official_detail', 'haod','haod.applicant_official_detail_id = hoa.applicant_official_detail_id');
	$query->innerJoin('housing_flat', 'hf','hf.flat_id = hfo.flat_id');
	$query->innerJoin('housing_estate', 'he','he.estate_id = hf.estate_id');
	$query->innerJoin('housing_district', 'hd','hd.district_code = he.district_code');
    $query->innerJoin('housing_flat_type', 'hft','hft.flat_type_id = hf.flat_type_id');
    // $query->innerJoin('housing_applicant', 'ha','ha.uid = haod.uid');   // Turned off by Subham Dt.22-04-2025
    $query->innerJoin('housing_applicant', 'ha','ha.housing_applicant_id = haod.housing_applicant_id'); // Done by Subham Dt.22-04-2025
    $query->innerJoin('housing_license_application', 'hla','hla.online_application_id = hoa.online_application_id');
    $query->innerJoin('housing_occupant_license', 'hol','hol.license_application_id = hla.license_application_id');
	$query->condition('hoa.online_application_id', $app_id, '=');
	//$query->condition('haod.is_active', '1', '=');   off by debaleena for license generated list 05/05/2025
	$query->addField('hoa', 'application_no');
	$query->addField('hfo', 'allotment_no');
	$query->addField('hfo', 'allotment_date');
	$query->addField('hfo', 'flat_id');
	$query->addField('he', 'estate_name');
	$query->addField('he', 'estate_address');
	$query->addField('hd', 'district_name');
	$query->addField('hfo', 'flat_occupant_id');
    $query->addField('hf', 'flat_no');
    $query->addField('hft', 'flat_type');
    $query->addField('ha', 'applicant_name');
    $query->addField('haod', 'applicant_designation');
    $query->addField('hol', 'license_no');

    $query->addField('hol', 'license_expiry_date');
	//$query->addField('haod', 'uid');

	$result = $query->execute(); 
	$result = $result->fetchObject();
    return $result;
}

/* end */