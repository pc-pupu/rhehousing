	
	
	/*function validate_user_profile_form(){
		//alert('OK');
		var formElements =
		{
			"name":["Username","userName"],
			"mail":["Email Address","emailAddress"],
			"pass[pass1]":["Password","passWordIfNotBlank"],
			"pass[pass2]":["Confirm Password","passWordIfNotBlank"]
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}*/
	
	
	function validate_user_login_form(form){
		//alert('OK');
		if(form.name.value != "" && form.pass.value != "" && form.captcha_response.value != ""){
			
			//this code for password encryption
			var x = btoa(btoa(btoa(form.pass.value)));
			if(form.pass.value != ""){
				jQuery("#edit-pass").val(x);
			}
			
			//for decryption refer to user module and see user.module file and go to function user_login_authenticate_validate($form, &$form_state) and comment off line //$password = trim($form_state['values']['pass']); and add new code $password = trim(base64_decode(base64_decode(base64_decode($form_state['values']['pass']))));	
			
		} else {
			var formElements =
			{
				"name":["Username","textBox"],
				"pass":["Password","textBox"],
				"captcha_response":["Captcha Code","textBox"],
			};	
		
			if(!validateForm(formElements)) {
				return false;
			} else {
				return true;
			}		
		}
		
	}
	
	
	function validate_request_new_password(){
		//alert('OK');
		var formElements =
		{
			"name":["Email Address","emailAddress"],
			"captcha_response":["Captcha Code","textBox"],
		};	
	
		if(!validateForm(formElements)) {
			return false;
		} else {
			return true;
		}
	}