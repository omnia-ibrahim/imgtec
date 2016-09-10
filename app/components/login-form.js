import Ember from 'ember';
//import UnauthenticatedRouteMixin from 'ember-simple-auth/mixins/unauthenticated-route-mixin';
import Flow from 'npm:flow-rest-client';

export default Ember.Component.extend({
    
    session: Ember.inject.service('session'),
    email: null,
    password: null,
    actions:{
        
         login: function () {
             
             var cdcRequest = new Flow.CDCRequest();
             cdcRequest.credentials.username = this.get('email');
             cdcRequest.credentials.password = this.get('password');
             console.log(cdcRequest);
             this.get('session').authenticate('authenticator:flow-authenticator', cdcRequest).catch((authError) => {
                 console.log('Authentication FAILED!!!' + authError);
             });
             
         }        
    }
});
