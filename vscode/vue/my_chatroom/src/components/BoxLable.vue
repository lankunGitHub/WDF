<script setup>
  import '@/assets/fonts/fonts.css'
</script>

<template>
  <div class="box_lable">
      <video class="background-video" autoplay muted loop>
      <source src="../assets/video/video.mp4" type="video/mp4">
      Your browser does not support the video tag.
    </video>
  </div>
</template>
  
<style scoped>
.box_lable {
  position: absolute;
  top: 2%;
  left: 2%;
  width: 25%;
  height: 40%;

  padding: 20px;
  /* 设置内边距 */
  border-radius: 25px;
}

.background-video {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  object-fit: cover;
  border-radius: 25px;
}
</style>
