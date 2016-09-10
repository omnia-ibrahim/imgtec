import Ember from 'ember';
import Base from 'ember-simple-auth/authorizers/base';

const {isEmpty} = Ember;

export default Base.extend({
    
    /**
     * Create relevant rest-api call headers for authenticated requests
     * 
     * @method authorize
     * @param {Object} data session data 
     * @param {Function} callback method that will receive a object containing relevant ajax call headers
     * @public
     */
    authorize(data, block){
        const accessToken = data.access_token;
        if (!isEmpty(accessToken)) {
            var headers = {'Authorization': 'Bearer ' + accessToken};
            block(headers);
        }        
    }
});