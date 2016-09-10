import Ember from 'ember';
import UnauthenticatedRouteMixin from 'ember-simple-auth/mixins/unauthenticated-route-mixin';
import Flow from 'npm:flow-rest-client';

export default Ember.Route.extend(UnauthenticatedRouteMixin, {
     session: Ember.inject.service('session'),
     isHasLayout: false,
 
     actions: {
         /** 
         login: function () {
             
             var cdcRequest = new Flow.CDCRequest();
             cdcRequest.credentials.username = this.get('email');
             cdcRequest.credentials.password = this.get('password');
             
            //  Ember.$('.')
             
             //cdcRequest.credentials.username = 'gillymukson@gmail.com';
             //cdcRequest.credentials.password = 'HhGhJ990';
             let {_username, _password} = this.getProperties('email', 'password');
             console.log('[Route:login] Username: '+ _username + 'Password: '+_password);
             console.log(cdcRequest);
             this.get('session').authenticate('authenticator:flow-authenticator', cdcRequest).catch((authError) => {
                 console.log('Authentication FAILED!!!' + authError);
             });
             //this.transitionTo('index');
         }
         **/
     }
});
