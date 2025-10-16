local _M = {}
local k8s_suffix = os.getenv("fqdn_suffix")
if (k8s_suffix == nil) then
  k8s_suffix = ""
end

function _M.PingTestService()
    local bridge_tracer = require "opentracing_bridge_tracer"
    local ngx = ngx
    local GenericObjectPool = require "GenericObjectPool"
    local TestServiceClient = require "social_network_TestService".TestServiceClient
    local client = GenericObjectPool:connection(
      TestServiceClient, "test-service" .. k8s_suffix, 9090)
    
    local status
    local err
    status, val = pcall(client.TestFunction, client)
    
    if not status then
      ngx.status = ngx.HTTP_INTERNAL_SERVER_ERROR
      ngx.say("Test function Failed: " .. err.message)
      ngx.log(ngx.ERR, "Follow Failed: " .. err.message)
      ngx.exit(ngx.HTTP_INTERNAL_SERVER_ERROR)
    end
    
    GenericObjectPool:returnConnection(client)
    ngx.log(ngx.ERR, "Succès dans l'appel au service de test")
    ngx.header["Content-Type"] = "text/plain; charset=utf-8"
    ngx.say(val)
    ngx.exit(ngx.HTTP_OK)


end 

return _M