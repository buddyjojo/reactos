
add_definitions(-D_MIDL_USE_GUIDDEF_)

list(APPEND SOURCE
#   access.idl
    asyncinfo.idl
    activation.idl
    activaut.idl
    activdbg.idl
    activscp.idl
    amstream.idl
    amvideo.idl
    asptlb.idl
#   asynot.idl
#   asysta.idl
    atliface.idl
    audioclient.idl
    audiopolicy.idl
    bdaiface.idl
#   binres.idl
    bits.idl
    bits1_5.idl
    bits2_0.idl
    bits2_5.idl
    bits3_0.idl
    bits5_0.idl
#   cmdbas.idl
#   cmdtxt.idl
    comcat.idl
    commoncontrols.idl
    control.idl
    cor.idl
    cordebug.idl
#   crtrow.idl
    ctffunc.idl
    ctxtcall.idl
    d2d1_1.idl
    d2d1_2.idl
    d2d1_3.idl
    d2d1.idl
    d2d1effectauthor.idl
    d2d1effects_1.idl
    d2d1effects_2.idl
    d2d1effects.idl
    d3d9on12.idl
    d3d10_1.idl
    d3d10.idl
    d3d10effect.idl
    d3d10sdklayers.idl
    d3d10shader.idl
    d3d11_1.idl
    d3d11_2.idl
    d3d11_3.idl
    d3d11_4.idl
    d3d11.idl
    d3d11on12.idl
    d3d11sdklayers.idl
    d3d12.idl
    d3d12sdklayers.idl
    d3d12shader.idl
    d3d12video.idl
    d3dx11core.idl
    ddstream.idl
#   dbccmd.idl
#   dbcses.idl
#   dbdsad.idl
#   dbinit.idl
#   dbprop.idl
#   dbs.idl
    dcommon.idl
    devenum.idl
    devicetopology.idl
    dimm.idl
    dispatcherqueue.idl
    dispex.idl
    dmodshow.idl
    docobj.idl
    docobjectservice.idl
    downloadmgr.idl
    dragdropinterop.idl
    drmexternals.idl
    dwrite_1.idl
    dwrite_2.idl
    dwrite_3.idl
    dwrite.idl
    dxgi.idl
    dxgi1_2.idl
    dxgi1_3.idl
    dxgi1_4.idl
    dxgi1_5.idl
    dxgi1_6.idl
    dxgicommon.idl
    dxgidebug.idl
    dxgiformat.idl
    dxgitype.idl
    dxva2api.idl
    dxvahd.idl
#   dyngraph.idl
    emptyvc.idl
    endpointvolume.idl
    exdisp.idl
    eventtoken.idl
    fusion.idl
    hlink.idl
    holographicspaceinterop.idl
    hstring.idl
    htiface.idl
    htiframe.idl
    httprequest.idl
    iads.idl
    icftypes.idl
    ieautomation.idl
    imnact.idl
    imnxport.idl
    indexsrv.idl
    inputscope.idl
    inseng.idl
    inspectable.idl
    mediaobj.idl
    metahost.idl
    mfidl.idl
    mfobjects.idl
    mftransform.idl
    mimeinfo.idl
    mimeole.idl
    mlang.idl
    mmc.idl
    mmdeviceapi.idl
    msaatext.idl
    mscoree.idl
    msctf.idl
    msdadc.idl
    mshtmhst.idl
    mshtml.idl
    msinkaut.idl
    mstask.idl
    msxml.idl
    msxml2.idl
    msxml6.idl
    natupnp.idl
    netcon.idl
    netfw.idl
    netlistmgr.idl
    oaidl.idl
    objectarray.idl
    objidl.idl
    objidlbase.idl
    objsafe.idl
    ocidl.idl
    ocmm.idl
    oleacc.idl
    oledb.idl
    oleidl.idl
#   opnrst.idl
    optary.idl
    perhist.idl
    propidl.idl
    propsys.idl
    pstore.idl
    restrictederrorinfo.idl
    richole.idl
    roparameterizediid.idl
#   row.idl
#   rowchg.idl
#   rstbas.idl
#   rstinf.idl
#   rstloc.idl
    rtworkq.idl
    sensevts.idl
    servprov.idl
#   sesprp.idl
    shdeprecated.idl
    shldisp.idl
    shobjidl.idl
    shtypes.idl
#   stdole2.idl
    strmif.idl
    structuredquerycondition.idl
    taskschd.idl
    textstor.idl
    tlogstg.idl
    tom.idl
    transact.idl
    tuner.idl
    txcoord.idl
    txdtc.idl
    uiautomationclient.idl
    uiautomationcore.idl
    unknwn.idl
    urlhist.idl
    urlmon.idl
    vmr9.idl
#   vmrender.idl
    vsbackup.idl
    vss.idl
    vswriter.idl
    wbemcli.idl
    wbemdisp.idl
    wbemprov.idl
    weakreference.idl
    wia_lh.idl
    wia_xp.idl
    wincodec.idl
    wincodecsdk.idl
    windows.system.idl
    windowscontracts.idl
    windows.foundation.idl
    windows.foundation.collections.idl
    windows.ui.idl
    windows.ui.core.idl
    windows.ui.input.idl
    windows.applicationmodel.idl
    windows.applicationmodel.activation.idl
    windows.applicationmodel.background.idl
    windows.applicationmodel.core.idl
    windows.applicationmodel.datatransfer.idl
    windows.applicationmodel.datatransfer.dragdrop.idl
    windows.applicationmodel.datatransfer.dragdrop.core.idl
    windows.data.json.idl
    windows.devices.bluetooth.idl
    windows.devices.enumeration.idl
    windows.devices.geolocation.idl
    windows.devices.haptics.idl
    windows.devices.input.idl
    windows.devices.power.idl
    windows.devices.usb.idl
    windows.foundation.metadata.idl
    windows.foundation.numerics.idl
    windows.gaming.input.idl
    windows.gaming.input.custom.idl
    windows.gaming.input.forcefeedback.idl
    windows.gaming.ui.idl
    windows.globalization.idl
    windows.graphics.idl
    windows.graphics.capture.idl
    windows.graphics.directx.idl
    windows.graphics.directx.direct3d11.idl
    windows.graphics.effects.idl
    windows.graphics.holographic.idl
    windows.graphics.imaging.idl
    windows.management.deployment.idl
    windows.media.idl
    windows.media.closedcaptioning.idl
    windows.media.devices.idl
    windows.media.speechrecognition.idl
    windows.media.speechsynthesis.idl
    windows.networking.idl
    windows.networking.connectivity.idl
    windows.perception.spatial.idl
    windows.perception.spatial.surfaces.idl
    windows.devices.radios.idl
    windows.security.authentication.onlineid.idl
    windows.security.credentials.idl
    windows.security.credentials.ui.idl
    windows.security.cryptography.idl
    windows.security.enterprisedata.idl
    windows.security.exchangeactivesyncprovisioning.idl
    windows.security.isolation.idl
    windows.storage.fileproperties.idl
    windows.storage.idl
    windows.storage.search.idl
    windows.storage.streams.idl
    windows.system.power.idl
    windows.system.profile.idl
    windows.system.profile.systemmanufacturers.idl
    windows.system.threading.idl
    windows.system.userprofile.idl
    windows.ui.composition.idl
    ivectorchangedeventargs.idl
    systemmediatransportcontrolsinterop.idl
    winsxs.idl
    wmcodecdsp.idl
    wmdrmsdk.idl
    wmiutils.idl
    wmsbuffer.idl
    wmsdkidl.idl
    wtypes.idl
    wuapi.idl
    xmldom.idl
    xmldso.idl
    ctfutb.idl
    xmllite.idl)

add_idl_headers(psdk ${SOURCE})
add_dependencies(psdk xdk)
add_typelib(stdole2.idl)
add_custom_target(stdole2 DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/stdole2.tlb)

add_idl_headers(d3d_idl_headers d3dcommon.idl)

add_iid_library(adsiid iads.idl transact.idl)
add_iid_library(mmc_uuids mmc.idl)
add_iid_library(wuguid wuapi.idl)
add_iid_library(xml_uuids msxml2.idl)

generate_idl_iids(wincodec.idl)
