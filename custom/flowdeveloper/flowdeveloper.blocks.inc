<?php
/**
 * @file
 * This file contains the function definitions for all FDW blocks in hook_block
 */

/**
 * Implements hook_block_info().
 */
function flowdeveloper_block_info() {
	$blocks = array();
	$blocks['footer'] = array(
		'info' => t('Footer'),
		'cache' => DRUPAL_CACHE_GLOBAL,
	);

	$blocks['CMS_Creator_Board_Kit'] = array(
		'info' => t('CMS Creator Board Kit'),
		'cache' => DRUPAL_CACHE_GLOBAL,
	);

	$blocks['CMS_IoT_Button_Project_Icon'] = array(
		'info' => t('CMS IoT Button Project Icon'),
		'cache' => DRUPAL_CACHE_GLOBAL,
	);

	$blocks['CMS_IoT_Coming_Soon_Icon'] = array(
		'info' => t('CMS IoT Coming Soon Icon'),
		'cache' => DRUPAL_CACHE_GLOBAL,
	);

	$blocks['CMS_Register_Device_Button'] = array(
		'info' => t('CMS Register Device Button'),
		'cache' => DRUPAL_CACHE_GLOBAL,
	);

	$blocks['CMS_Sign_Up_Button'] = array(
		'info' => t('CMS Sign Up Button'),
		'cache' => DRUPAL_CACHE_GLOBAL,
	);

	return $blocks;
}

/**
 * Implements hook_block_view_MODULE_DELTA_alter().
 * MODULE is flowdeveloper. DELTA is footer.
 */
function flowdeveloper_block_view_flowdeveloper_footer_alter(&$data, $block) {
	$data['content'] = array(
		'#theme' => 'flowdeveloper_footer',
	);
}

/**
 * Implements hook_block_info_alter().
 * added footer menus as block
 */
/*function flowdeveloper_block_info_alter(&$blocks, $theme, $code_blocks) {
	if ($theme == variable_get('theme_default', '0')) {
		// move menu links to footer
		$blocks['menu']['footer-menu-1']['region'] = 'footer';
		$blocks['menu']['footer-menu-1']['status'] = 1;

		$blocks['menu']['footer-menu-2']['region'] = 'footer';
		$blocks['menu']['footer-menu-2']['status'] = 1;

		$blocks['menu']['footer-menu-3']['region'] = 'footer';
		$blocks['menu']['footer-menu-3']['status'] = 1;
	}
}*/

/**
 * Implements hook_block_view().
 */
function flowdeveloper_block_view($delta = '') {
	$block = array();

	switch ($delta) {
		case 'CMS_Creator_Board_Kit':
			$block['subject'] = '';
			$block['content'] = _flowdeveloper_block_creator_board_kit();
			break;

		case 'CMS_IoT_Button_Project_Icon':
			$block['subject'] = '';
			$block['content'] = _flowdeveloper_block_iot_button_project_icon();
			break;

		case 'CMS_IoT_Coming_Soon_Icon':
			$block['subject'] = '';
			$block['content'] = _flowdeveloper_block_iot_coming_soon_icon();
			break;

		case 'CMS_Register_Device_Button':
			$block['subject'] = '';
			$block['content'] = _flowdeveloper_block_register_device_button();
			break;

		case 'CMS_Sign_Up_Button':
			$block['subject'] = '';
			$block['content'] = _flowdeveloper_block_sign_up_button();
			break;
	}

	return $block;
}

function _flowdeveloper_block_creator_board_kit() {
	$theme_path = base_path() . drupal_get_path('theme',$GLOBALS['theme']);
	$output = <<<HTML
<div class="cms-creator-kit-map">
	<img src="$theme_path/images/Creator-Board_Kit.jpg" alt="">
	<div class="cms-creator-kit-hotspots">
		<div><button title="" data-content="The micro USB cable can be used to power any of the Creator kit boards as well as providing a method for debug or programming functions on the different boards." data-placement="top" data-trigger="focus" data-toggle="popover" class="cms-creator-kit-hotspot p1" data-original-title="Micro USB cable"></button></div>
		<div><button title="" data-content="Connect a USB pen drive containing the OpenWRT linux distribution to the Ci40 board using the micro USB to USB type A socket adapter cable." data-placement="top" data-trigger="focus" data-toggle="popover" class="cms-creator-kit-hotspot p2" data-original-title="Micro USB socket adapter"></button></div>
		<div><button title="" data-content="Ci40 provides the backbone to your Creator Kit. Connectivity options include an Ethernet socket, 802.11 B/G/N/AC wifi, Bluetooth Low Energy, and 6LowPAN to provide connection to the included PIC Clicker boards. Ci40 has a Raspberry Pi connector as well as a pair of MikroBus sockets to provide multiple expansion possibilities." data-placement="top" data-trigger="focus" data-toggle="popover" class="cms-creator-kit-hotspot p3" data-original-title="Ci40"></button></div>
		<div><button title="" data-content="The PIC32MX 6LoWPAN clicker boards provide the remote device development platform and have a MikroBus socket to accept CLICK add on modules as well as a pair of buttons and LEDs for user defined functions. Power can be provided using the dual AAA battery holder on the back of the board or via the micro USB cable." data-placement="top" data-trigger="focus" data-toggle="popover" class="cms-creator-kit-hotspot p4" data-original-title="6LoWPAN PIC Clicker"></button></div>
		<div><button title="" data-content="The click modules can be added to the Ci40 and Clicker boards to add sensor and control options. The Creator kit pack includes the Motion click proximity sensor module, the Thermo 2 temperature sensor module, and the Relay click two way relay module" data-placement="top" data-trigger="focus" data-toggle="popover" class="cms-creator-kit-hotspot p5" data-original-title="Click module pack"></button></div>
	</div>
</div>
HTML;

	return $output;
}

function _flowdeveloper_block_iot_button_project_icon() {
	$link_path = base_path()."home-automation-kit/iot-button";
	$theme_path = base_path() . drupal_get_path('theme',$GLOBALS['theme']);

	$output = <<<HTML
	<a class="c-ate-hak-button-project-icon" href="$link_path">
		<img src="$theme_path/images/IoT_button_project.jpg" class="img-responsive" alt="">
	</a>
HTML;

	return $output;
}

function _flowdeveloper_block_iot_coming_soon_icon() {
	$theme_path = base_path() . drupal_get_path('theme',$GLOBALS['theme']);

	$output = <<<HTML
	<img src="$theme_path/images/projects_coming_soon.jpg" class="img-responsive" alt="">
HTML;

	return $output;
}

function _flowdeveloper_block_register_device_button() {
	$link_path = base_path()."dashboard/devices/register";

	$output = <<<HTML
<div class="centered text-center">
	<a role="button" class="c-ate-hak-iot-register-ci40 btn btn-primary" href="$link_path">Register Ci40</a>
</div>
HTML;

	return $output;
}

function _flowdeveloper_block_sign_up_button() {
	$link_path = base_path()."user/register";

	$output = <<<HTML
<div class="centered text-center">
	<a role="button" class="c-ate-hak-iot-signup c-hak-iot-signup btn btn-primary" href="$link_path">Sign up</a>
</div>
HTML;

	return $output;
}