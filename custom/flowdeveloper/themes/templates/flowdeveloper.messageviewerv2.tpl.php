<style type="text/css">
	.material-switch > input[type="checkbox"] {
		display: none;
	}

	.material-switch > label {
		cursor: pointer;
		height: 0px;
		position: relative;
		width: 40px;
	}

	.material-switch > label::before {
		background: rgb(0, 0, 0);
		box-shadow: inset 0px 0px 10px rgba(0, 0, 0, 0.5);
		border-radius: 5px;
		content: '';
		height: 12px;
		margin-top: -4px;
		position:absolute;
		opacity: 0.3;
		transition: all 0.4s ease-in-out;
		width: 35px;
	}
	.material-switch > label::after {
		background: rgb(255, 255, 255);
		border-radius: 5px;
		box-shadow: 0px 0px 5px rgba(0, 0, 0, 0.3);
		content: '';
		height: 20px;
		left: -4px;
		margin-top: -5px;
		position: absolute;
		top: -4px;
		transition: all 0.3s ease-in-out;
		width: 24px;
	}
	.material-switch > input[type="checkbox"]:checked + label::before {
		background: inherit;
		opacity: 0.5;
	}
	.material-switch > input[type="checkbox"]:checked + label::after {
		background: inherit;
		left: 20px;
	}

	.notice {
		padding: 5px;
		background-color: #fafafa;
		border-left: 6px solid #7f7f84;
		margin-bottom: 10px;
		-webkit-box-shadow: 0 5px 8px -6px rgba(0,0,0,.2);
		-moz-box-shadow: 0 5px 8px -6px rgba(0,0,0,.2);
		box-shadow: 0 5px 8px -6px rgba(0,0,0,.2);
	}
	.notice-info {
		border-color: #9b5c97;
	}

	#sip-log{
		max-height:700px !important;  height:700px !important;
		overflow: auto;
	}

	.panel-heading {
		font-weight:700;
	}

	.sip-container {
		border-bottom:1px solid #e7e7e7;
		margin-bottom: 15px;
	}

	.page-footer{
		text-align: center;
	}

	.page-header-sub {
		background-color: #f3f3f3;
		color: #9b5c97;
		font-size: 18px;
		padding-left:9px;
		font-family: 'Open Sans', sans-serif;
		font-weight: 500;
		padding-top: 10px !important;
		padding-bottom: 10px !important;
	}

	.page-description-sub {
		font-size: 11px;
		color: #707070;
		padding-left: 9px;
		padding-bottom: 20px;
		font-family: 'Open Sans', sans-serif;
	}

</style>

<?php drupal_set_title('Messages'); ?>

<div class="container-fluid">

	<div class="page-header-sub">Pub/Sub Message Viewer</div>
	<div class="page-description-sub">Subscribe to topics to receive messages published to them.</div>

	<h3 class="form-signin-heading hidden">Creator Message Viewer - <small>Pub/Sub support</small></h3>
	<div class="container-fluid sip-container">
		<div class="row">
			<div class="col-xs-12 col-sm-5 col-md-4 col-lg-3" style="padding-left:0;">
				<div class="panel panel-default">
					<!-- Default panel contents -->
					<div class="panel-heading">User Topics</div>

					<!-- List group -->
					<ul class="list-group">
						<?php $array_count = 0; ?>
						<?php foreach ($data['user_fm_topics'] as $topic): ?>
							<li class="list-group-item">
								<?php print $topic['Name']; ?>
								<div class="material-switch pull-right">
									<input id="user-topic-<?php print $array_count;?>" class="c-topic-subscribe" data-checked="false" data-topic-name="<?php print $topic['Name']; ?>" name="user-topic-<?php print $array_count;?>" type="checkbox"/>
									<label for="user-topic-<?php print $array_count;?>" class="label-default"></label>
								</div>
							</li>
							<?php $array_count++; ?>
						<?php endforeach; ?>
					</ul>


					<div class="panel-heading">Device Topics</div>

					<!-- List group -->
					<ul class="list-group">
						<?php $array_count = 0; ?>
						<?php foreach ($data['device_fm_topics'] as $device_topics): ?>
							<div class="panel-heading">Device: <?php print $device_topics['DeviceName']; ?></div>
								<?php foreach ($device_topics['items'] as $topic): ?>
									<li class="list-group-item">
										<?php print $topic['Name']; ?>
										<div class="material-switch pull-right">
											<input id="device-topic-<?php print $array_count;?>" class="c-topic-subscribe" data-checked="false" data-is-device-topic="true" data-client-id="<?php print $device_topics['DeviceID']; ?>" data-topic-name="<?php print $topic['Name']; ?>" name="device-topic-<?php print $array_count;?>" type="checkbox"/>
											<label for="device-topic-<?php print $array_count;?>" class="label-default"></label>
										</div>
									</li>
									<?php $array_count++; ?>
								<?php endforeach; ?>
						<?php endforeach; ?>
					</ul>

				</div>
			</div>
			<div class="col-xs-12 col-sm-8 col-md-9">
				<div id="sip-log" class="panel">

				</div>
			</div>
		</div>
	</div>
	<div class="page-footer">
		If you are using the deprecated point-to-point SIP messaging, click <a class="" href="<?php print url(FDW_DASHBOARD).'/'.FDW_MESSAGE_VIEWER_V2; ?>" title="<?php print t('SIP Messages'); ?>"><?php print t('here'); ?></a> to see your messages.
	</div>
</div>
