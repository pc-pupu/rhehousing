<?php
	// split the username and password so we can put the form links were we want (they are in the "user-login-links" div bellow)
	print drupal_render($form['name']);
	print drupal_render($form['pass']);
	print drupal_render($form['captcha']);
?>
	
<?php
	// render login button
	print drupal_render($form['form_build_id']);
	print drupal_render($form['form_id']);
	print drupal_render($form['actions']);
?>
<div class="user-login-links">
	<?php
	global $base_url;
	?>
	<span class="password-link"><a href="<?php print $base_url; ?>/hrms-login">Click here for HRMS login</a></span>	
</div>

<!-- <div class="user-login-links">
<span class="password-link"><a href="/user/password">Forget your password?</a></span> | 
<span class="register-link"><a href="/user/register">Create an account</a></span>
</div> -->
	
