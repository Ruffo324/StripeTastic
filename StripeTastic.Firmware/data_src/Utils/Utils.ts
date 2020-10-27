/**
 * Contains util function's for url manipulation.
 */
export module UrlManipulation {

    /**
     * Return the value of the url get parameter.
     * @param parameterName The name of the wanted get parameter.
     * @returns {string} The value of the get parameter or undefined.
     */
    export function GetParameter(parameterName: string): string {
        var getValues: {} = {};
        location.search.substr(1).split("&").forEach(item => { getValues[item.split("=")[0]] = item.split("=")[1] });
        return getValues[parameterName];
    }

    /**
     * Sets the value for a get url parameter.
     * Leave value empty, to delete a get parameter.
     * @param parameterName Name of the get parameter.
     * @param value Value of the get parameter.
     */
    export function SetGetParameter(parameterName: string, value?: string): void {
        var getValues: {} = {};
        location.search.substr(1).split("&").forEach(item => { getValues[item.split("=")[0]] = item.split("=")[1] });
        getValues[parameterName] = [value];

        let newSearch: string = "";
        Object.keys(getValues).forEach((key) => {
            if (getValues.hasOwnProperty(key) && key !== "" && getValues[key] !== "") {
                newSearch += `&${key}=${getValues[key]}`;
            }
        });
        if (newSearch.length > 0)
            newSearch = newSearch.substr(1);

        history.pushState({}, "", `?${newSearch}`);
    }
}