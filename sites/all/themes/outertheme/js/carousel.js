window.onload = function () {
    var mySwiper = new Swiper(".swiper-container", {
        direction: "vertical",
        loop: true,
        pagination: ".swiper-pagination",
        grabCursor: true,
        speed: 10000,
        paginationClickable: true,
        parallax: true,
        autoplay: true,
        effect: "slide",
        mousewheelControl: 1
    })
};