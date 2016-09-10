<style type="text/css">

	input[type="text"] {
		border-bottom-left-radius: 0;
		border-bottom-right-radius: 0;
		margin-bottom: 5px;
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
	.notice-sm {
		padding: 10px;
		font-size: 80%;
	}
	.notice-lg {
		padding: 35px;
		font-size: large;
	}

	.notice-info {
		border-color: #9b5c97;
	}
	.notice-info>strong {
		color: #9b5c97;
	}

	.page-header-sub {
		background-color: #9b5c97;
		color: #FFF;
		font-size: 18px;
		padding-left:9px;
		font-family: 'Open Sans', sans-serif;
		font-weight: 500;
		padding-top: 10px !important;
		padding-bottom: 10px !important;
	}

	.page-description-sub{
		font-size: 11px;
		color: #707070;
		padding-left: 9px;
		padding-bottom: 20px;
		font-family: 'Open Sans', sans-serif;
	}

	.btn-primary{
		background-color: #9b5c97 !important;
		border-color: #9b5c97 !important;
		margin-bottom: 10px;
	}

	.message-date-time {
		padding: 10px 10px 10px 10px;
	}

	.page-description-sub {
		padding-left: 5px !important;
	}

</style>

<?php drupal_set_title("SIP Messages"); ?>

<span class="c-device-back-arrow c-ate-device-back-arrow hidden">
	<a href="<?php print base_path().'/dashboard/'.FDW_MESSAGE_VIEWER_V2;?>">
		<img src="<?php print base_path().'/sites/all/themes/highness/images/icons/back-arrow.png';?>"/>
		<span class="c-back-arrow-text">Messages</span>
	</a>
</span>

<div class="container-fluid">

	<div class="page-header-sub">SIP Message Viewer</div>
	<div class="page-description-sub">This message viewer displays deprecated point-to-point SIP messages. We recommend that you use the new topic-based <a href="<?php print base_path().'/dashboard/'.FDW_MESSAGE_VIEWER;?>">Pub/Sub messaging.</a></div>

	<h3 class="form-signin-heading hidden">Creator Message Viewer - <small>SIP via Websocket</small></h3>

	<div class="container-fluid">
		<div id="message-viewer-tool-box" class="row">
			<button data-entity-id="all" class="c-message-filter-button btn btn-primary btn-md active">All</button>
			<button id="clear-log" class="btn btn-md btn-primary pull-right">Clear log</button>
		</div> <br/>

		<div id="log" class="row" style="overflow-y: auto; max-height: 600px;"></div>
	</div>

</div>
