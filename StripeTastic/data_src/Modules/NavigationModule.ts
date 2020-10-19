import { UrlManipulation } from "../Utils/Utils";

export module NavigationModule {
    const defaultPage: string = "./pages/led-config.html";

    export function Bind(): void {

        $(".nav-link").on("click", (element) => {
            let clickedItem = $(element.target);
            let targetPage = clickedItem.data("page-file-name");

            loadPage(targetPage);
        });

        LoadPageFromUrl(); // Load url by checking the current link.
    }

    export function LoadPageFromUrl(): void {
        const pageParameterValue: string = UrlManipulation.GetParameter("page");
        if (typeof pageParameterValue === "undefined")
            loadPage(defaultPage);
        else
            loadPage(pageParameterValue);
    }

    function loadPage(pageFile: string): void {
        $("#container-page").load(pageFile);
        $(".nav-item").removeClass("active");
        $(`.nav-item[data-page-file-name="${pageFile}"]`).parent().addClass("active");
    }
}