import Ember from 'ember';
import Base from 'ember-simple-auth/authenticators/base';
import Flow from 'npm:flow-rest-client';  

const {isEmpty} = Ember;

export default Base.extend({
    
    flowAuthenticationService: new Flow.AuthServices(),
    
    
    restore(data){
        
        data = data || {};
        return new Ember.RSVP.Promise((resolve, reject) => {
           if (!isEmpty(data)) {
               const NOW = (new Date()).getTime();
               if ( (!isEmpty(data.expires_at) && (data.expires_at < NOW) ) ) {
                   /**
                    * refresh the access_token if a refresh token is available
                    */
                    if (data.refresh_token) {
                        
                        Ember.run(() => {
                            var flowAuthenticationService = this.get('flowAuthenticationService');
                            var request = new Flow.CDCRequest();
                            request.credentials.refresh_token = data.refresh_token;
                            var authPromise = flowAuthenticationService.refresh_token(request);
                            authPromise.then((sessionData) => {
                                /**
                                 * Alert the session service to update the session data with the new access_token
                                 */
                                //console.log('[flow-authenticator:restore()] SessionData::');
                                //console.log(sessionData);
                                this.trigger('sessionDataUpdated', sessionData);
                                resolve(sessionData);
                            }, (authenticationError) => {
                                reject(authenticationError);
                            });                            
                        });

                    } else {
                        reject();
                    }
               }
               else if(!isEmpty(data.access_token)) {
                   resolve(data);
               } else {
                   reject();
               }
           } else {
               reject();
           } 
        });
    },    
    
    /**
     * Authenticates the user session using the supplied credentials in the CDCRequest object
     * The CDCRequest object should contain a credentials obect that contains a username and a password field that can be accessible like:
     * CDCRequest.credentials.username and CDCRequest.credentials.password
     * 
     * @method authenticate
     * @param {Object} a CDCRequest object 
     * @return {Ember.RSVP.Promise} A promise that when it resolves, results in the session becoming authenticated
     * @public    
     */
    authenticate(CDCRequest){
        
        //console.log('[flow-authenticator::authenticate] CDCRequest:: ');
        //console.log(CDCRequest);
        return new Ember.RSVP.Promise((resolve, reject) => {
            if ( (!isEmpty(CDCRequest)) && (!isEmpty(CDCRequest.credentials.username)) && (!isEmpty(CDCRequest.credentials.password)) ) 
            {
                // console.log('[flow-authenticator::authenticate] Valid Credentials ');
                var flowAuthenticationService = this.get('flowAuthenticationService');
                var authPromise = flowAuthenticationService.authenticate_user(CDCRequest);
                authPromise.then((sessionData) => {
                    resolve(sessionData);
                }, (authenticationError) => {
                    reject(authenticationError);                  
                });    
            }
            else
            {
                var errorMsg = 'The supplied CDCRequest object cannot be empty. It needs to have a \
                                CDCRequest.credentials.username and CDCRequest.credentials.password property';
                reject(errorMsg);
            }
            
        }); 
        
    },
    
    /**
     * Invalidate the current session. In the case of the Developer Console, the access_token provided by Flow lasts only the duration of
     * the user's session so there is nothing extra to do in this invalidate method.  The session service that calls this authenticator will clear
     * the session data stored in the session store.
     * 
     * @method invalidate
     * @param {Obect} data The current authenticated session data
     * @return {Ember.RSVP.Promise} A promise that when it resovles, results in the session service clearing all the session data else, the session remains authenticated
     * @public
     */
    invalidate(data){
        return Ember.RSVP.resolve();
    }, 

    
    
});