
	function setCookie(name,value) {
		var days = 365;
		var expires = "";
		if (days) {
			var date = new Date();
			date.setTime(date.getTime() + (days*24*60*60*1000));
			expires = "; expires=" + date.toUTCString();
		}
		document.cookie = name + "=" + (value || "")  + expires + "; path=/";
	}
	function getCookie(name) {
		var nameEQ = name + "=";
		var ca = document.cookie.split(';');
		for(var i=0;i < ca.length;i++) {
			var c = ca[i];
			while (c.charAt(0)==' ') c = c.substring(1,c.length);
			if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
		}
		return null;
	}
	function eraseCookie(name) {   
		document.cookie = name+'=; Max-Age=-99999999;';  
	}	
	
	
	jQuery(document).ready(function(){
		// Reset font-size
		var defaultsize = jQuery('*').children().css('font-size');
		
		jQuery("#medium").click(function(){
			
			jQuery('*').children().css('font-size', defaultsize);
			
			jQuery('#toolbar *').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#toolbar *').css('font-size', '10.998px');
				return false;
			});
			jQuery('.td_no_data_found').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.td_no_data_found').css('font-size', '18px');
				return false;
			});
			jQuery('#breadcrumb').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#breadcrumb').css('font-size', '14px');
				return false;
			});
			jQuery('#breadcrumb a').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#breadcrumb a').css('font-size', '14px');
				return false;
			});
			jQuery('.form-item .description').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.form-item .description').css('font-size', '12px');
				return false;
			});
			jQuery('label').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('label').css('font-size', '14px');
				return false;
			});
			jQuery('.fieldset-legend a').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.fieldset-legend a').css('font-size', '17px');
				return false;
			});
			jQuery('.form-item input.form-text').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.form-item input.form-text').css('font-size', '12px');
				return false;
			});
			jQuery('.button').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.button').css('font-size', '11px');
				return false;
			});
			jQuery('.node-readmore a').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.node-readmore a').css('font-size', '14px');
				return false;
			});
			jQuery('.breadcrumb_links').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.breadcrumb_links').css('font-size', '14px');
				return false;
			});
			jQuery('.sidebar h2').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.sidebar h2').css('font-size', '20px');
				return false;
			});
			jQuery('table th').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('table th').css('font-size', '14px');
				return false;
			});
			jQuery('table td').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('table td').css('font-size', '12px');
				return false;
			});
			jQuery('table td a').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('table td a').css('font-size', '12px');
				return false;
			});
			jQuery('#contact1 b').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#contact1 b').css('font-size', '32px');
				return false;
			});
			jQuery('#contact2').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#contact2').css('font-size', '24px');
				return false;
			});
			jQuery('#contact3').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#contact3').css('font-size', '16px');
				return false;
			});
			jQuery('.description a').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('.description a').css('font-size', '15px');
				return false;
			});
			
			
			jQuery('h1').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('h1').css('font-size', '28px');
				return false;
			});
			jQuery('h2').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('h2').css('font-size', '21px');
				return false;
			});
			jQuery('h3').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('h3').css('font-size', '16.38px');
				return false;
			});
			jQuery('#date-time').each(function(){
				jQuery(this).css('font-size', '');
				jQuery('#date-time').css('font-size', '13px');
				return false;
			});
			
			return false;
		});
		
		// Increase font-size
		jQuery("#large").click(function(){
			
			var currentfontsize = jQuery('*').children().css('font-size');
			var incfontsize = parseFloat(currentfontsize, 10);
			var newsize = incfontsize*1.2;
			jQuery('*').children().css('font-size', newsize);
			
			jQuery('h1').each(function(){
				jQuery(this).css('font-size', '');
				var h1_currentfontsize = jQuery('h1').css('font-size');
				var h1_incfontsize = parseFloat(h1_currentfontsize, 10);
				var h1_newsize = h1_incfontsize*1.2;
				jQuery('h1').css('font-size', h1_newsize);
				
				return false;
			});
				
			jQuery('h2').each(function(){
				jQuery(this).css('font-size', '');
				var h2_currentfontsize = jQuery('h2').css('font-size');
				var h2_incfontsize = parseFloat(h2_currentfontsize, 10);
				var h2_newsize = h2_incfontsize*1.2;
				jQuery('h2').css('font-size', h2_newsize);
				
				return false;
			});
			
			jQuery('h3').each(function(){
				jQuery(this).css('font-size', '');
				var h3_currentfontsize = jQuery('h3').css('font-size');
				var h3_incfontsize = parseFloat(h3_currentfontsize, 10);
				var h3_newsize = h3_incfontsize*1.2;
				jQuery('h3').css('font-size', h3_newsize);
				
				return false;
			});
			
			return false;
		});
		
		// Decrease font-size
		jQuery("#small").click(function(){
			
			var currentfontsize = jQuery('*').children().css('font-size');
			var decfontsize = parseFloat(currentfontsize, 10);
			var newsize = decfontsize*0.8;
			jQuery('*').children().css('font-size', newsize);
			
			jQuery('h1').each(function(){
				jQuery(this).css('font-size', '');
				var h1_currentfontsize = jQuery('h1').css('font-size');//alert(h1_currentfontsize);
				var h1_incfontsize = parseFloat(h1_currentfontsize, 10);
				var h1_newsize = h1_incfontsize*0.8;
				jQuery('h1').css('font-size', h1_newsize);
				
				return false;
			});
				
			jQuery('h2').each(function(){
				jQuery(this).css('font-size', '');
				var h2_currentfontsize = jQuery('h2').css('font-size');
				var h2_incfontsize = parseFloat(h2_currentfontsize, 10);
				var h2_newsize = h2_incfontsize*0.8;
				jQuery('h2').css('font-size', h2_newsize);
				
				return false;
			});
			
			jQuery('h3').each(function(){
				jQuery(this).css('font-size', '');
				var h3_currentfontsize = jQuery('h3').css('font-size');
				var h3_incfontsize = parseFloat(h3_currentfontsize, 10);
				var h3_newsize = h3_incfontsize*0.8;
				jQuery('h3').css('font-size', h3_newsize);
				
				return false;
			});
			
			return false;
		});
		
		
		function contrastColor() {
			/*jQuery("*").children().css("background-color", "#000000");
			jQuery("*").children().css("color", "#fffa2f");*/
			
			jQuery("*").children().addClass('theme-yellow');
		}
		
		function defaultColor() {
			jQuery('*').children().removeClass('theme-yellow');
		}
		
		var colorScheme = getCookie('colorScheme');
		if(colorScheme == 'contrast') {
			contrastColor();
		} 
		if(colorScheme == 'default') {
			defaultColor();
		}
		jQuery(".contrast_color").click(function() {
			setCookie('colorScheme', 'contrast');
			contrastColor();
		});
		jQuery(".default_color").click(function() {
			setCookie('colorScheme', 'default');
			defaultColor();
		});
		
	 });