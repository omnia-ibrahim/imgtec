<?php if (isset($FCAPCode)) { ?>
			
			<div class="cn-device-reg">
				<div class="cn-wrapper col-xs-12 col-md-8 col-md-offset-2">
					<div class="cp-help row">
						<div class="cn-icon-wrapper col-xs-1 col-sm-1">
							<div class="cp-icon"></div>
						</div>
						<div class="cp-copy col-xs-11 col-sm-11">
							<?php
							
								if (!isset($_COOKIE[FDW_DEVICE_REG_COOKIE_NAME])) 
								{
									$info = 'Register a device to start using Creator services & resources. '
									  . 'Registration will associate the device with your account and make you the device\'s owner. '
									  . 'This will give you access to all of the device\'s resources, management functions and operational data. '
									  . 'Likewise the device will have access to your settings and preferences. '	
									  ; 
									print t($info); 
								}
							?>
							<div class="text-center center-block">
								<div class="c-got-it-btn btn btn-default c-ate-device-reg-gotit-btn"><?php print t('Got it')?></div>
							</div>
						</div>
					</div>
					<div class="cn-cloud-computing-wrapper row">
						<div class="cp-cloud-computing center-block col-xs-12"><img src="<?php print url(drupal_get_path('theme', 'highness').'/images/ilustration.png'); ?>" class="img-responsive"></div>
					</div>					
					<div class="cn-intro-wrapper row">
						<div class="cp-intro col-xs-12">
							<div class="center-block"><?php print t('Register your device with the code below to associate it with your account.'); ?></div>
							<div class="c-fcapcode center-block c-ate-device-reg-fcapcode">
								<div class="q-code"><?php print $FCAPCode['fcapcode'];  ?></div>
								<div class="q-exp"><span class="cp-copy"><?php print ' Expires on ';?></span><?php print utcTimeToDate($FCAPCode['expdate']);  ?></div>
							</div>
						</div>
					</div>
					<div class="cn-device-types-wrapper row">
						<div class="cp-device-types col-xs-12">
							<div class="center-block"><?php print t('For instructions about how to use this code please select the type of device you are registering:'); ?></div>
							<div class="cp-dt-form center-block"><?php print render($deviceTypesForm); ?></div>
							<div class="c-devicereg-instruction c-ate-device-reg-guide">
							</div>
						</div>
					</div>
				</div>
			</div>
			
<?php	}else{ // NO FCAPCode ?>
		<div class="cn-device-reg row">
			<div class="cn-wrapper col-xs-12 col-md-8 col-md-offset-2">
				<div class="cn-intro-wrapper row">
					<div class="cp-intro col-xs-12">
						<div class="text-center center-block">
							<?php
								$copy = 'You have already registered the maximum number of devices allowed under your account.';	 
								print t($copy); 
							?>
						</div>
						<!--  <div class="text-center center-block">
							<div class="c-upgrade-btn btn btn-default c-ate-device-reg-upgrade-btn"><?php //print t('Upgrade Now')?></div>
						</div>-->
					</div>
				</div>
			</div>
		</div>
<?php 	}?>
