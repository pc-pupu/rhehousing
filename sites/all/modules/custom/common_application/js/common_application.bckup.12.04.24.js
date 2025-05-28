	/*jQuery(document).ready(function() {
		jQuery('.designation_selectize').select2();
	});*/

	/*jQuery(document).ready(function() {
		jQuery('.select2 .select2-container .select2-container--default').css('width', '317px');
	});*/
	
jQuery(document).ready(function() {
	
	jQuery("#mobile_no").keypress(function (e)  
	{ 
	  if( e.which!=8 && e.which!=0 && (e.which<48 || e.which>57))
	  {
	    return false;
      }	
	});
	
	
	jQuery(".numeric_positive").keypress(function (e)  
	{ 
	  if( e.which!=8 && e.which!=0 && (e.which<48 || e.which>57))
	  {
	    return false;
      }	
	});
	
});

jQuery(document).ready(function(){
		jQuery("#edit-dob").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		changeMonth: true,
		changeYear: true,
		//yearRange: "-70:-18",
		yearRange: "-70:-18", //18 years or older up to 70year (oldest person ever, can be sensibly set to something much smaller in most cases)
	    maxDate: "-18Y", //Will only allow the selection of dates more than 18 years ago, useful if you need to restrict this
		autoSize: true
	});	
});

jQuery(document).ready(function(){
		jQuery("#edit-doj").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		changeMonth: true,
		changeYear: true,
		yearRange: "-70:+0",
		maxDate: "0",
		autoSize: true
	});	
});

jQuery(document).ready(function(){
		jQuery("#edit-dor").datepicker({
		dateFormat: "dd/mm/yy",
		//minDate: minDoj,
		changeMonth: true,
		changeYear: true,
		yearRange: "-0:+70",
		minDate: "0",
		autoSize: true
	});	
});

/*jQuery(document).ready(function(){
	
	   var dob = jQuery('#edit-dob').val();
       var dob_arr =  dob.split("/");
	   var day = parseInt(dob_arr[0]) ;
	   var month = parseInt(dob_arr[1]);
	   var year = parseInt(dob_arr[2]) + 18 ;
	   var minDoj = day +'/'+ month +'/'+ year; 
	  
	  
		jQuery("#edit-doj").datepicker({
		dateFormat: "dd/mm/yy",
		minDate: minDoj,
		changeMonth: true,
		changeYear: true,
		yearRange: "-70:+0",
		autoSize: true
	});
	
});*/

/*jQuery(document).ready(function(){
    jQuery('.cutcopypasteoff').bind("cut copy paste",function(e) {
        e.preventDefault();
    });
});*/


/*function isNumberKey(evt) {
    var charCode = (evt.which) ? evt.which : event.keyCode;
    if (charCode != 46 && charCode > 31
    && (charCode < 48 || charCode > 57))
        return false;

    return true;
}*/

	function validate_common_application_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"applicant_name":["Applicant's Name","alphabetFullstop"],
			"applicant_father_name":["Father's / Husband's Name","alphabetFullstop"],
			
			"permanent_street":["Permanent Address", "streetAddress"],
			"permanent_city_town_village":["City / Town / Village", "onlyAlphabet"],
			"permanent_post_office":["Post Office", "hyphenFullStop"],
			"permanent_district":["District", "selectBox"],
			"permanent_pincode":["Pincode", "onlyNo"],
		}
		
		//if(jQuery("#chk_present_address").not(':checked')) {
		if(jQuery("#edit-chk-permanent-address-1").not(':checked')) {
			var formElements1 = 
			{
				"present_street":["Present Address", "streetAddress"],
				"present_city_town_village":["City / Town / Village", "onlyAlphabet"],
				"present_post_office":["Post Office", "hyphenFullStop"],
				"present_district":["District", "selectBox"],
				"present_pincode":["Pincode", "onlyNo"],
			}
			formElements = jQuery.extend(formElements, formElements1);
		}
		
		var formElements2 =
		{
			"dob":["Date of Birth","date"],
			"gender":["Gender", "radioBox"],
			"mobile":["Mobile No", "mobileNo"],
			"email":["Email Id", "emailAddress"],
			
			"hrms_id":["Employee HRMS ID", "hrmsId"],
			"app_designation":["Designation", "textArea"],
			"pay_band":["Pay Band", "selectBox"],
			"pay_in":["Pay in the Pay Band", "onlyNo"],
			"grade_pay":["Grade Pay", "onlyNo"],
			//"gpf_no":["GPF No", "gpfNo"],
			"app_posting_place":["Place of Posting", "onlyAlphabet"],
			"app_headquarter":["Headquarter", "onlyAlphabet"],
			"doj":["Date of Joining", "date"],
			"dor":["Date of Retirement", "date"],
			
			"office_name":["Name of the Office", "textArea"],
			"office_street":["Office Address", "streetAddress"],
			"office_city":["City / Town / Village", "onlyAlphabet"],
			"office_post_office":["Post Office", "hyphenFullStop"],
			"office_district":["District", "selectBox"],
			"office_pincode":["Pincode", "onlyNo"],
			"office_phone_no":["Telephone No.", "telephoneNo"],
			
			"district":["DDO District", "selectBox"],
			"designation":["DDO Designation", "selectBox"]
			
		};
		
		formElements = jQuery.extend(formElements, formElements2);
		
		return formElements;	
	
		/*if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}*/
	}
	
	
	
	/*jQuery(document).ready(function(){
	
		jQuery('#chk_present_address').click(function () {
			if(jQuery(this).is(':checked')) {
				jQuery('#present_street').hide();
				jQuery('#present_city_town_village').hide();
				jQuery('#present_post_office').hide();
				jQuery('#present_district').hide();
				jQuery('#present_pincode').hide();
				
				jQuery('#present_street').val('');
				jQuery('#present_city_town_village').val('');
				jQuery('#present_post_office').val('');
				jQuery('#present_district').val('');
				jQuery('#present_pincode').val('');
				
				jQuery('#edit-present-address').hide();
			
			} else if(jQuery(this).not(':checked')) {
				jQuery('#present_street').show();
				jQuery('#present_city_town_village').show();
				jQuery('#present_post_office').show();
				jQuery('#present_district').show();
				jQuery('#present_pincode').show();
				
				jQuery('#edit-present-address').show();
			
			}
		});
	
	});
	
	jQuery(document).ready(function(){
		if(jQuery('#chk_extra_doc').is(':checked')) {
			jQuery('#present_street').hide();
			jQuery('#present_city_town_village').hide();
			jQuery('#present_post_office').hide();
			jQuery('#present_district').hide();
			jQuery('#present_pincode').hide();
			
			jQuery('#present_street').val('');
			jQuery('#present_city_town_village').val('');
			jQuery('#present_post_office').val('');
			jQuery('#present_district').val('');
			jQuery('#present_pincode').val('');
			
			jQuery('#edit-present-address').hide();
		} else {
			jQuery('#present_street').show();
			jQuery('#present_city_town_village').show();
			jQuery('#present_post_office').show();
			jQuery('#present_district').show();
			jQuery('#present_pincode').show();
			
			jQuery('#edit-present-address').show();
		}	
	});*/

