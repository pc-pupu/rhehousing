<?php

/**
 * Add body classes if certain regions have content.
 */
function outertheme_preprocess_html(&$variables) {
  if (!empty($variables['page']['featured'])) {
    $variables['classes_array'][] = 'featured';
  }

  if (!empty($variables['page']['triptych_first'])
    || !empty($variables['page']['triptych_middle'])
    || !empty($variables['page']['triptych_last'])) {
    $variables['classes_array'][] = 'triptych';
  }

  if (!empty($variables['page']['footer_firstcolumn'])
    || !empty($variables['page']['footer_secondcolumn'])
    || !empty($variables['page']['footer_thirdcolumn'])
    || !empty($variables['page']['footer_fourthcolumn'])) {
    $variables['classes_array'][] = 'footer-columns';
  }

  // Add conditional stylesheets for IE
  drupal_add_css(path_to_theme() . '/css/ie.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie6.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 6', '!IE' => FALSE), 'preprocess' => FALSE));

  drupal_add_http_header('X-Generator', '');
  
}

/**
 * Override or insert variables into the page template for HTML output.
 */
function outertheme_process_html(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_html_alter($variables);
  }
}

/**
 * Override or insert variables into the page template.
 */
function outertheme_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
  // Since the title and the shortcut link are both block level elements,
  // positioning them next to each other is much simpler with a wrapper div.
  if (!empty($variables['title_suffix']['add_or_remove_shortcut']) && $variables['title']) {
    // Add a wrapper div using the title_prefix and title_suffix render elements.
    $variables['title_prefix']['shortcut_wrapper'] = array(
      '#markup' => '<div class="shortcut-wrapper clearfix">',
      '#weight' => 100,
    );
    $variables['title_suffix']['shortcut_wrapper'] = array(
      '#markup' => '</div>',
      '#weight' => -99,
    );
    // Make sure the shortcut link is the first item in title_suffix.
    $variables['title_suffix']['add_or_remove_shortcut']['#weight'] = -100;
  }
}

/**
 * Implements hook_preprocess_maintenance_page().
 */
function outertheme_preprocess_maintenance_page(&$variables) {
  // By default, site_name is set to Drupal if no db connection is available
  // or during site installation. Setting site_name to an empty string makes
  // the site and update pages look cleaner.
  // @see template_preprocess_maintenance_page
  if (!$variables['db_is_active']) {
    $variables['site_name'] = '';
  }
  drupal_add_css(drupal_get_path('theme', 'outertheme') . '/css/maintenance-page.css');
}

/**
 * Override or insert variables into the maintenance page template.
 */
function outertheme_process_maintenance_page(&$variables) {
  // Always print the site name and slogan, but if they are toggled off, we'll
  // just hide them visually.
  $variables['hide_site_name']   = theme_get_setting('toggle_name') ? FALSE : TRUE;
  $variables['hide_site_slogan'] = theme_get_setting('toggle_slogan') ? FALSE : TRUE;
  if ($variables['hide_site_name']) {
    // If toggle_name is FALSE, the site_name will be empty, so we rebuild it.
    $variables['site_name'] = filter_xss_admin(variable_get('site_name', 'Drupal'));
  }
  if ($variables['hide_site_slogan']) {
    // If toggle_site_slogan is FALSE, the site_slogan will be empty, so we rebuild it.
    $variables['site_slogan'] = filter_xss_admin(variable_get('site_slogan', ''));
  }
}

/**
 * Override or insert variables into the node template.
 */
function outertheme_preprocess_node(&$variables) {
  if ($variables['view_mode'] == 'full' && node_is_page($variables['node'])) {
    $variables['classes_array'][] = 'node-full';
  }
}

/**
 * Override or insert variables into the block template.
 */
function outertheme_preprocess_block(&$variables) {
  // In the header region visually hide block titles.
  if ($variables['block']->region == 'header') {
    $variables['title_attributes_array']['class'][] = 'element-invisible';
  }
}

/**
 * Implements theme_menu_tree().
 */
function outertheme_menu_tree($variables) {
  return '<ul class="menu clearfix">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_field__field_type().
 */
function outertheme_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<h3 class="field-label">' . $variables['label'] . ': </h3>';
  }

  // Render the items.
  $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
  foreach ($variables['items'] as $delta => $item) {
    $output .= '<li class="taxonomy-term-reference-' . $delta . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</li>';
  }
  $output .= '</ul>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '"' . $variables['attributes'] .'>' . $output . '</div>';

  return $output;
}

// function outertheme_theme() {
// 	$items = array();
//  	$items['user_login'] = 	array(
// 					'render element' => 'form',
// 					'path' => drupal_get_path('theme', 'outertheme') . '/templates',
// 					'template' => 'user-login'
// 	);	
		
// 	return $items;
// }

function outertheme_preprocess_page(&$variables) {
  if (user_is_anonymous()) {
    $variables['theme_hook_suggestions'][] = 'header';
    $variables['theme_hook_suggestions'][] = 'footer';
  } else {
    $variables['theme_hook_suggestions'][] = 'header_after_login';
    $variables['theme_hook_suggestions'][] = 'footer_after_login';
  }
}

function outertheme_block_info(){
  $blocks['custom'] = array('info' => t('Custom block modulename'));
  return $blocks;
}

function outertheme_form_user_login_alter(&$form, &$form_state, $form_id) {
  
  drupal_set_title(t('Admin Sign in to Continue'));
  $form['name']['#attributes'] = array('class'=>array('form-control input-form-custom'),'autocomplete'=>'off','placeholder'=>'Enter Username', 'maxlength'=>100);
  $form['pass']['#attributes'] = array('class'=>array('form-control input-form-custom'),'autocomplete'=>'off','placeholder'=>'Enter Password', 'maxlength'=>100);
  $form['op']['#attributes'] = array('class'=>array('admin-login-btn btn-block custom-btn-rounded'));

  if ($form_id == 'user_login') {
		$form['s_val'] = array('#type' => 'hidden',
			'#attributes' => array('id' => array('s_val')),
			'#size' => 60,
			'#maxlength' => 125,
			// '#required' => TRUE,
		  );
		$form['ct_val'] = array('#type' => 'hidden',
			'#attributes' => array('id' => array('ct_val')),
			'#size' => 60,
			'#maxlength' => 125,
			// '#required' => TRUE,
		  );  
	}
	$form['#attributes']['onsubmit'] = 'pwd_handler(this);';
}

function outertheme_form_user_pass_alter(&$form, &$form_state, $form_id) {

  $form['#title'] = t('Reset Your Password');
  $form['name']['#attributes'] = array('class'=>array('form-control input-form-custom'),'autocomplete'=>'off','placeholder'=>'Enter Registered E-mail Address', 'maxlength'=>100);
  $form['op']['#attributes'] = array('class'=>array('admin-login-btn btn-block custom-btn-rounded'));

}


