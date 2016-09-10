import Ember from 'ember';

export default Ember.Component.extend({
    click(e) {
        // Only want to do this for mobile        
        var windowWidth = Ember.$(window).width();
        if(windowWidth > 1024) {
            return;
        } 
        
        var drawerMenu = Ember.$(e.target).parents('.mdl-layout__drawer'),
            obfuscator = drawerMenu.siblings('.mdl-layout__content').children('.mdl-layout__obfuscator'),
            drawerBtn = drawerMenu.siblings('.mdl-layout__drawer-button');
            
        if(drawerMenu.hasClass('is-visible') && windowWidth < 1025){
            obfuscator.removeClass("is-visible");
            drawerMenu.removeClass("is-visible");
        }
    }
});