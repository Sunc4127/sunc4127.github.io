<template>
  <div v-html="markdownToHtml"></div>
</template>

<script>
 
import file from './docs/Java/_01_Data_structure.md'

export default {
  name: 'App',
  data() {
    return {
      markdown: file
    }
  },
  computed: {
    markdownToHtml() {
      return this.md(this.markdown);
    }
  },
/*   created() {
    var client = new XMLHttpRequest();
    client.open('GET', './docs/data_Structure_and_Algorithm/_01_data_structure.md');

    client.onreadystatechange = function() {
        this.markdown = client.responseText;
    }
    client.send();
  }, */
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
