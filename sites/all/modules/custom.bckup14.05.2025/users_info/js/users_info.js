/*jQuery(document).ready(function(){
	//alert('ok');
	jQuery('#edit-roles-8').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-division').show();
        	//alert('checked');
      
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-division').hide();
			//alert('not checked');
     
        }
    });
	 
	  
	jQuery('#edit-roles-7').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-division').show();
			jQuery('.form-item-subdiv').show();
        	//alert('checked');
      
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-division').hide();
			jQuery('.form-item-subdiv').hide();
			//alert('not checked');
     
        }
    });
	  
	  
});

jQuery(document).ready(function(){
	if (jQuery('#edit-roles-8').is(':checked')) {
		jQuery('.form-item-division').show();
	//alert('checked');
  
	} else {
		jQuery('.form-item-division').hide();
		//alert('not checked');
 
	}
	
	if (jQuery('#edit-roles-7').is(':checked')) {
		jQuery('.form-item-division').show();
		jQuery('.form-item-subdiv').show();
	//alert('checked');
  
	} else {
		jQuery('.form-item-division').hide();
		jQuery('.form-item-subdiv').hide();
		//alert('not checked');
 
	}  
	  
});*/

/*jQuery(document).ready(function(){
	jQuery('#edit-roles-3').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-roles-6').hide();
			jQuery('.form-item-roles-7').hide();
			jQuery('.form-item-roles-8').hide();
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-roles-6').show();
			jQuery('.form-item-roles-7').show();
			jQuery('.form-item-roles-8').show();
        }
    });
	
	jQuery('#edit-roles-6').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-roles-3').hide();
			jQuery('.form-item-roles-7').hide();
			jQuery('.form-item-roles-8').hide();
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-roles-3').show();
			jQuery('.form-item-roles-7').show();
			jQuery('.form-item-roles-8').show();
        }
    });
	
	jQuery('#edit-roles-8').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-roles-3').hide();
			jQuery('.form-item-roles-6').hide();
			jQuery('.form-item-roles-7').hide();
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-roles-3').show();
			jQuery('.form-item-roles-6').show();
			jQuery('.form-item-roles-7').show();
        }
    });
	
	jQuery('#edit-roles-7').click(function () {
        if (jQuery(this).is(':checked')) {
			jQuery('.form-item-roles-3').hide();
			jQuery('.form-item-roles-6').hide();
			jQuery('.form-item-roles-8').hide();
        } else if (jQuery(this).not(':checked')) {
			jQuery('.form-item-roles-3').show();
			jQuery('.form-item-roles-6').show();
			jQuery('.form-item-roles-8').show();
        }
    }); 
});*/


	function validate_user_createform(){
		var formElements;
		formElements1 =
		{
			
			//"designation":["Designation","onlyAlphabet"],
			"name":["Username","userName"],
			"pass[pass1]":["Password","passWord"],
			"pass[pass2]":["Confirm Password","passWord"],
			"mail":["Email","emailAddress"],
		};
		formElements = jQuery.extend(formElements, formElements1);
		
		if(jQuery("#edit-roles-8").is(':checked')) {
			formElements2 = {
				"division":["Select Division","selectBox"],
				"full_name":["Name","onlyAlphabet"],
				"mobile_no":["Mobile No.","mobileNo"],
				"office_phone_no":["Telephone No.", "telephoneNo"],
			};
			formElements = jQuery.extend(formElements, formElements2);
		} 
		else if(jQuery("#edit-roles-7").is(':checked')) {
			formElements2 = {
				"division":["Select Division","selectBox"],
				"subdiv":["Select Sub-Division","selectBox"],
				"full_name":["Name","onlyAlphabet"],
				"mobile_no":["Mobile No.","mobileNo"],
				"office_phone_no":["Telephone No.", "telephoneNo"],
			};
			formElements = jQuery.extend(formElements, formElements2);
		}
		else if(jQuery("#edit-roles-6").is(':checked')) {
			formElements2 = {
				"full_name":["Name","onlyAlphabet"],
				"mobile_no":["Mobile No.","mobileNo"],
				"office_phone_no":["Telephone No.", "telephoneNo"],
			};
			formElements = jQuery.extend(formElements, formElements2);
		}
		else if(jQuery("#edit-roles-9").is(':checked')) {
			formElements2 = {
				"full_name":["Name","onlyAlphabet"],
				"mobile_no":["Mobile No.","mobileNo"],
				"office_phone_no":["Telephone No.", "telephoneNo"],
			};
			formElements = jQuery.extend(formElements, formElements2);
		}
		else if(jQuery("#edit-roles-10").is(':checked')) {
			formElements2 = {
				"full_name":["Name","onlyAlphabet"],
				"mobile_no":["Mobile No.","mobileNo"],
				"office_phone_no":["Telephone No.", "telephoneNo"],
			};
			formElements = jQuery.extend(formElements, formElements2);
		}
		//alert(validateForm(formElements));
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	function validate_user_editform(){
		var formElements =
		{
			"full_name":["Name","onlyAlphabet"],
			//"designation":["Designation","onlyAlphabet"],
			"pass[pass1]":["Password","passWordIfNotBlank"],
			"pass[pass2]":["Confirm Password","passWordIfNotBlank"],
			"mail":["Email address","emailAddress"],
			"mobile_no":["Mobile No.","mobileNo"],
			"office_phone_no":["Telephone No.", "telephoneNo"],
			"division":["Select Division","selectBox"],
			"subdiv":["Select Sub-Division","selectBox"]
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	
	function validate_user_profile_edit_form(){
		var formElements =
		{
			"full_name":["Name","onlyAlphabet"],
			"email":["Email address","emailAddress"],
			"mobile_no":["Mobile No.","mobileNo"],
			"office_phone_no":["Telephone No.", "telephoneNo"],
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}
	