
	function validate_new_complaint_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"complaint_type":["Complaint Type","selectBox"],
			
		};
		
		var complaint_type = jQuery('#edit-complaint-type').val();
		
		if(complaint_type == 'Other') {
			var formElements1 =
			{
				"complaint_other_type":["Compalint Other Type","onlyAlphabet"],
			}
			formElements = jQuery.extend(formElements, formElements1);		
		}
		
		var formElements2 =
		{
			"complaints_details":["The specific details of the complaint","textArea"],
		}
		formElements = jQuery.extend(formElements, formElements2);
			
		
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}	
	}
	
	
	function validate_action_report_form(){
		//alert('OK'); 
		//return false;
		var formElements =
		{
			"subdivn_action_report":["Action Report", "textArea"],
			"action_report_accepted":["Do you want to accept Sub-Division Action Report as Final Action Report?", "radioBox"],
			
		};
		
		var action_report_accepted = jQuery('#edit-action-report-accepted-n').val();
		
		if(action_report_accepted == 'N') {
			var formElements1 =
			{
				"divn_action_report":["Final Action Report","textArea"]
			}
			formElements = jQuery.extend(formElements, formElements1);
		}
		
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}	
	}