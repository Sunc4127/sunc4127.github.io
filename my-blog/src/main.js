import { createApp } from 'vue'
import App from './App.vue'
import { marked } from 'marked'

const markedMixin = {
    methods: {
        md: function (input) {
            return marked(input);
        }
    }
}

createApp(App).mixin(markedMixin).mount("#app");
