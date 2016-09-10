import Ember from 'ember';
import config from './config/environment';

const Router = Ember.Router.extend({
  location: config.locationType
});

Router.map(function() {
  this.route('clients');
  this.route('metrics');
  this.route('client', { path: '/client/:client_id' }, function() {
    this.route('metrics');
    this.route('certificates');
    this.route('details');
  });
  this.route('account');
  this.route('access-keys');
  this.route('certificates');
  this.route('login');
});

export default Router;