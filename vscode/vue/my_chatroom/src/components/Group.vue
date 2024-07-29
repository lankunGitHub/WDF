<script setup>
  import { ref } from 'vue'
  
</script>

<template>
  <div class="grouplist">
    <input type="search" class="search_css" placeholder="输入群聊名">
    群聊
  </div>
</template>


<style scoped>
.grouplist {
  background-color: blue;
  overflow-y: auto;
}

.search_css {
  position: relative;
  top: -49%;
  left: 0%;
  width: 100%;
  height: 5%;

  font-size: 30%;
}
</style>