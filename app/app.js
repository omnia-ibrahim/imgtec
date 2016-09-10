import Ember from 'ember';
import Resolver from './resolver';
import loadInitializers from 'ember-load-initializers';
import config from './config/environment';

let App;

Ember.MODEL_FACTORY_INJECTIONS = true;

App = Ember.Application.extend({
  modulePrefix: config.modulePrefix,
  podModulePrefix: config.podModulePrefix,
  Resolver
});


Ember.Route = Ember.Route.extend({
      isHasLayout: true,
      setupController: function(controller, model) {
        this._super(controller, model);
        this.controllerFor('application').set('isHasLayout', this.get('isHasLayout'));
      }
    });
    
    
loadInitializers(App, config.modulePrefix);

export default App;
