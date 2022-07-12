/**
 * @callback RenameFile
 * @param {string} fileSrcRelativePath
 * @param {string} fileDstRelativePath
 * @returns {Promise<void>}
 */

/**
 * @callback ReplaceInFile
 * @param {string} fileRelativePath
 * @param {string} searchValue
 * @param {string} newValue
 * @returns {Promise<void>}
 */

/**
 * @typedef {Object} WizardContext
 * @property {string} projectDirPath
 * @property {string} projectName
 * @property {RenameFile} renameFile
 * @property {ReplaceInFile} replaceInFile
 */

/**
 * @param {WizardContext} context
 */
async function postProcessing(context) {
    await context.replaceInFile("CMakeLists.txt", "eez-flow-template-sdl", context.projectName);

    await context.replaceInFile("README.md", "{{projectDirPath}}", context.projectDirPath);
    await context.replaceInFile("README.md", "{{projectName}}", context.projectName);

    await context.replaceInFile("src/platform/simulator/win32/icon.rc", "{{projectName}}", context.projectName);
    
    await context.replaceInFile("src/platform/simulator/emscripten/index.html", "{{projectName}}", context.projectName);

    await context.replaceInFile("src/main.cpp", "eez-flow-template-sdl", context.projectName);

    await context.replaceInFile("src/gui/app_context.cpp", "eez-flow-template-sdl", context.projectName);

    await context.renameFile("eez-flow-template-sdl.eez-project", context.projectName + ".eez-project");

    await context.replaceInFile("template/manifest.json", "{{projectName}}", context.projectName);
}

module.exports = postProcessing;