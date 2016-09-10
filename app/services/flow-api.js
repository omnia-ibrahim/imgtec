import Ember from 'ember';
import Flow from 'npm:flow-rest-client';

export default Ember.Service.extend({
    ClientServices: new Flow.ClientServices(),
    init() {
        this._super(...arguments);
    },
    get_clients() {
        var ClientServices = this.get('ClientServices');
        return ClientServices.get_clients();
    },
    get_client_details(client_id) {
        var ClientServices = this.get('ClientServices');           
        return ClientServices.get_client_details(client_id);
    },
    get_client_property(client_id, property){
        var ClientServices = this.get('ClientServices');           
        return ClientServices.get_client_property(client_id, property);
    }
});
