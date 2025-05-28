<?php
	global $user;
	global $user_role;

	$query = db_select('housing_applicant', 'ha');
	$query->innerJoin('users', 'u', 'u.uid = ha.uid');
	$query->fields('ha', array('applicant_name', 'date_of_birth', 'mobile_no'));
	$query->fields('u', array('mail'));

	$query->condition('ha.uid', $user->uid, '=');

	$result = $query->execute();
	$row_count = $result->rowCount();
	if($row_count > 0) {
		$data = $result->fetchObject();
		//global $user_info;
		//$user_info = $data->applicant_name;
	}
	
	$query1 = db_select('users_details', 'ud');
	$query1->innerJoin('users', 'u', 'u.uid = ud.uid');
	$query1->fields('ud', array('full_name', 'mobile_no'));
	$query1->fields('u', array('mail'));

	$query1->condition('ud.uid', $user->uid, '=');
	$result1 = $query1->execute();

	//echo "<pre>";print_r($data1);die;
	$row_count1 = $result1->rowCount();
	if($row_count1 > 0) {
		$data1 = $result1->fetchObject();
		//global $user_info;
		//$user_info = $data->applicant_name;
	}
	//echo "<pre>";print_r($data1);die;
?>

<div class="user-profile">

	<?php if($user_role == 4 || $user_role == 5) : ?>
    	<br>
    	<table align="center" width="100%">

            <font style="font-size:16px"> <?php print 'Name - '.$data->applicant_name;?></font> <br>
            <font style="font-size:16px"> <?php print 'Date of Birth - '.trim( implode('/', array_reverse(explode('-', $data->date_of_birth))));?></font> <br>
            <font style="font-size:16px"> <?php print 'Mobile No. - '.$data->mobile_no;?></font> <br>
            <font style="font-size:16px"> <?php print 'Email Id - '.$data->mail;?></font>
        </table>
    <?php elseif($user_role == 8 || $user_role == 7 || $user_role == 6 || $user_role == 9 || $user_role == 10 || $user_role == 11) : ?>
    	<br>
    	<table align="center" width="100%">
    		
            <!-- <font style="font-size:16px"> <?php //print 'Name - '.$data1->full_name;?></font> <br>
            <font style="font-size:16px"> <?php //print 'Mobile No. - '.$data1->mobile_no;?></font> <br>
            <font style="font-size:16px"> <?php //print 'Email Id - '.$data1->mail;?></font> -->
            <font style="font-size:16px"> Name -<?php if(isset($data1->full_name)) { echo $data1->full_name; }?></font> <br>
            <font style="font-size:16px"> Mobile No. -<?php if(isset($data1->mobile_no)) { echo $data1->mobile_no; }?></font> <br>
            <font style="font-size:16px"> Email Id -<?php if(isset($data1->mail)) { echo $data1->mail; }?></font>
        </table>
    <?php elseif($user_role == 3) : ?>
    	<br>
    	<table align="center" width="100%">
            <font style="font-size:16px"> 
				System Administrator – </font><font style="font-size:16px">This is an ITS owned role.  The Site Administrator controls the configuration of the entire Drupal install.  They control the system wide preferences, installs updates and modules, set up sites, and have responsibility for pushes from a “sandbox” to Production.
            </font>
        </table>
        
    <?php /*?><?php elseif($user_role == 6) : ?>
    	<br>
    	<table align="center" width="100%">
            <font style="animation:running; font-size:16px"> 
				<marquee behavior="alternate">Welcome Housing Admin</marquee>
            </font>
        </table> <?php */?>
            
	<?php endif; ?>



</div>