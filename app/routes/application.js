import Ember from 'ember';
import ApplicationRouteMixin from 'ember-simple-auth/mixins/application-route-mixin';

export default Ember.Route.extend(ApplicationRouteMixin, {
    model(){
        
    },
    actions: {
       handle_menu: function (params) {
           Ember.$('.mdl-layout__obfuscator').toggleClass("is-visible");
       }
    }

});
